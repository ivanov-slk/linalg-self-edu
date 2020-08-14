#pragma once
#include <tuple>
#include "matrix.hpp"
#include "qr_decomposition.hpp"

template <Number T>
class SVD2x2Decomposer; // implementation below

/**
 * @brief Performs an SVD decomposition using Jacobi rotation method.
 */
template <Number T>
class SVDDecomposer
{
public:
    Matrix<T> matrix_u;
    Matrix<T> matrix_v;
    Matrix<T> matrix_s;
    void operator()(const Matrix<T> &matrix)
    {
        // get shape and transpose if necessary
        int n_rows = matrix.get_shape().first;
        int n_cols = matrix.get_shape().second;
        bool transpose = false;
        Matrix<T> matrix_b;
        if (n_rows >= n_cols)
        {
            matrix_b = matrix;
        }
        else
        {
            matrix_b = matrix.transpose();
            std::swap(n_rows, n_cols);
            transpose = true;
        }

        // initialize the output matrices
        matrix_u = MakeDiagonal<T>()(1., n_rows, n_rows);
        matrix_v = MakeDiagonal<T>()(1., n_cols, n_cols);

        // Adjust the matrices
        QRDecomposer<T> qr;
        qr(matrix_b);
        matrix_b = qr.matrix_r;
        matrix_u = matrix_u.multiply(qr.matrix_q.transpose());

        // Set the convergence criteria
        T eps = 0.000000000001;
        T n_squared = matrix_b.sum(-1, 2).extract_element(0, 0); // sum() always returns a matrix
        T tolerance = eps * eps * n_squared;
        T convergence_status = T(0);
        int counter = 0; // not needed, but kept for debugging

        do
        {
            convergence_status = T(0);
            for (int i = 0; i < n_cols - 1; ++i)
            {
                for (int j = i + 1; j < n_cols; ++j)
                {
                    convergence_status = convergence_status + std::pow(matrix_b.extract_element(i, j), 2) + std::pow(matrix_b.extract_element(j, i), 2);

                    SVD2x2Decomposer<T> svd_2x2;
                    auto [c1, s1, c2, s2, d1, d2] = svd_2x2(
                        matrix_b.extract_element(i, i),
                        matrix_b.extract_element(i, j),
                        matrix_b.extract_element(j, i),
                        matrix_b.extract_element(j, j));

                    // create the right and left rotation matrices
                    Matrix<T> matrix_left_rot = MakeDiagonal<T>()(T(1), n_rows, n_rows);
                    matrix_left_rot.set_element(c1, i, i);
                    matrix_left_rot.set_element(c1, j, j);
                    matrix_left_rot.set_element(-s1, i, j);
                    matrix_left_rot.set_element(s1, j, i);

                    Matrix<T> matrix_right_rot = MakeDiagonal<T>()(T(1), n_cols, n_cols);
                    matrix_right_rot.set_element(c2, i, i);
                    matrix_right_rot.set_element(c2, j, j);
                    matrix_right_rot.set_element(-s2, i, j);
                    matrix_right_rot.set_element(s2, j, i);

                    // update the decomposition matrices
                    matrix_b = matrix_left_rot.multiply(matrix_b).multiply(matrix_right_rot.transpose());
                    matrix_u = matrix_left_rot.multiply(matrix_u);
                    matrix_v = matrix_right_rot.multiply(matrix_v);
                    counter++;
                }
            }
        } while (convergence_status > tolerance);

        // remove unnecessary "almost-zeros"
        matrix_s = MakeDiagonal<T>()(matrix_b);

        // transpose back if necessary
        if (transpose == false)
        {
            matrix_u = matrix_u.transpose();
        }
        else
        {
            matrix_s = matrix_s.transpose();
            matrix_v = matrix_v.transpose();
            std::swap(matrix_u, matrix_v);
        }
    }
};

/**
 * @brief Helper functor that performs RQ decomposition on 2x2 matrix using Givens rotations.
 * Accepts and returns raw values, not a matrix.
 */
template <Number T>
class RQ2x2Decomposer
{
public:
    std::tuple<T, T, T, T, T> operator()(T a, T b, T c, T d)
    {
        T x = 0;
        T y = 0;
        T z = 0;
        T c2 = 0;
        T s2 = 0;

        // std::cout << "my c: " << c << "\n";
        if (c == 0)
        {
            x = a;
            y = b;
            z = d;
            c2 = 1;
            // std::cout << "my short\n";
            return std::tuple{x, y, z, s2, c2};
        }
        T max_denom = std::max(std::abs(c), std::abs(d));
        T recip_max_denom = 1 / max_denom;
        c *= recip_max_denom;
        d *= recip_max_denom;

        T denom = 1 / std::sqrt(c * c + d * d);

        T numer_x = (-b * c + a * d);
        T numer_y = (a * c + b * d);
        x = numer_x * denom;
        y = numer_y * denom;
        z = max_denom / denom;
        s2 = -c * denom;
        c2 = d * denom;

        // std::cout << "my long\n";
        return std::tuple{x, y, z, s2, c2};
    }
};

/**
 * @brief Helper functor that calculates the SVD decomposition of 2x2 matrix.
 * Accepts and returns raw values, not a matrix.
 *
 * Follows this SO answer with minor modifications:
 * https://scicomp.stackexchange.com/a/28506/36712
 */
template <Number T>
class SVD2x2Decomposer
{
public:
    std::tuple<T, T, T, T, T, T> operator()(T a, T b, T c, T d)
    {
        T c1, s1, d1, d2;

        // Calculate RQ decomopsition of A
        auto [x, y, z, s2, c2] = RQ2x2Decomposer<T>()(a, b, c, d);

        // Calculate tangent of rotation on R[x, y; theta; z] to diagonalize R^T*R
        T scaler = T(1) / std::max(std::abs(x), std::abs(y));
        T x_ = x * scaler;
        T y_ = y * scaler;
        T z_ = z * scaler;
        T numer = ((z_ - x_) * (z_ + x_)) + y_ * y_;
        T gamma = x_ * y_;
        gamma = numer == 0 ? 1 : gamma;
        T zeta = numer / gamma;

        T sign_zeta = (numer < 0) ? -1 : 1; // numer is never zero, see above
        T t = 2 * sign_zeta / (std::abs(zeta) + std::sqrt(zeta * zeta + 4));

        // Calculate sines and cosines
        c1 = T(1) / std::sqrt(T(1) + t * t);
        s1 = c1 * t;

        // Calculate U * S = R * R(c1, s1)
        T usa = c1 * x - s1 * y;
        T usb = s1 * x + c1 * y;
        T usc = -s1 * z;
        T usd = c1 * z;

        // Update V = R(c1, s1)^T * Q
        t = c1 * c2 + s1 * s2;
        s2 = c2 * s1 - c1 * s2;
        c2 = t;

        // Separate U and S
        d1 = std::hypot(usa, usc);
        d2 = std::hypot(usb, usd);
        T dmax = std::max(d1, d2);
        T usmax1 = d2 > d1 ? usd : usa;
        T usmax2 = d2 > d1 ? usb : -usc;

        T sign_d1 = (x * z == 0) ? 0 : ((x * z < 0) ? -1 : 1);
        dmax *= d2 > d1 ? sign_d1 : 1;
        d2 *= sign_d1;
        T recip_dmax = 1 / dmax;

        c1 = dmax != T(0) ? usmax1 * recip_dmax : T(1);
        s1 = dmax != T(0) ? usmax2 * recip_dmax : T(0);

        return std::tuple<T, T, T, T, T, T>{c1, s1, c2, s2, d1, d2};
    }
};