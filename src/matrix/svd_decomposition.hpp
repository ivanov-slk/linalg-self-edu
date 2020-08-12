#pragma once
#include <tuple>
#include "matrix.hpp"
#include "qr_decomposition.hpp"

// template <class T>
// void Rq2x2Helper(const Matrix<T>& A, T& x, T& y, T& z, T& c2, T& s2) {
//     T a = A.extract_element(0, 0);
//     T b = A.extract_element(0, 1);
//     T c = A.extract_element(1, 0);
//     T d = A.extract_element(1, 1);

//     std::cout << "c: " << c << "\n";
//     if (c == 0) {
//         x = a;
//         y = b;
//         z = d;
//         c2 = 1;
//         s2 = 0;
//         std::cout << "short\n";
//         return;
//     }
//     T maxden = std::max(abs(c), abs(d));

//     T rcmaxden = 1/maxden;
//     c *= rcmaxden;
//     d *= rcmaxden;

//     T den = 1/sqrt(c*c + d*d);

//     T numx = (-b*c + a*d);
//     T numy = (a*c + b*d);
//     x = numx * den;
//     y = numy * den;
//     z = maxden/den;

//     s2 = -c * den;
//     c2 = d * den;
//     std::cout << "long";
// }


// template <class T>
// void Svd2x2Helper(const Matrix<T>& A, T& c1, T& s1, T& c2, T& s2, T& d1, T& d2) {
//     // Calculate RQ decomposition of A
//     T x, y, z;
//     Rq2x2Helper(A, x, y, z, c2, s2);

//     // Calculate tangent of rotation on R[x,y;0,z] to diagonalize R^T*R
//     T scaler = T(1)/std::max(std::abs(x), std::abs(y));
//     T x_ = x*scaler, y_ = y*scaler, z_ = z*scaler;
//     T numer = ((z_-x_)*(z_+x_)) + y_*y_;
//     T gamma = x_*y_;
//     gamma = numer == 0 ? 1 : gamma;
//     T zeta = numer/gamma;

//     T sign_zeta = (numer < 0) ? -1 : 1;
//     T t = 2*sign_zeta/(abs(zeta) + sqrt(zeta*zeta+4));

//     // Calculate sines and cosines
//     c1 = T(1) / sqrt(T(1) + t*t);
//     s1 = c1*t;

//     // Calculate U*S = R*R(c1,s1)
//     T usa = c1*x - s1*y;
//     T usb = s1*x + c1*y;
//     T usc = -s1*z;
//     T usd = c1*z;

//     // Update V = R(c1,s1)^T*Q
//     t = c1*c2 + s1*s2;
//     s2 = c2*s1 - c1*s2;
//     c2 = t;

//     // Separate U and S
//     d1 = std::hypot(usa, usc);
//     d2 = std::hypot(usb, usd);
//     T dmax = std::max(d1, d2);
//     T usmax1 = d2 > d1 ? usd : usa;
//     T usmax2 = d2 > d1 ? usb : -usc;

//     T signd1 = (x * z == 0) ? 0 : ((x * z < 0) ? -1 : 1);
//     dmax *= d2 > d1 ? signd1 : 1;
//     d2 *= signd1;
//     T rcpdmax = 1/dmax;

//     c1 = dmax != T(0) ? usmax1 * rcpdmax : T(1);
//     s1 = dmax != T(0) ? usmax2 * rcpdmax : T(0);
// }

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
        int counter = 0;

        do
        {
            convergence_status = T(0);
            for (int i = 0; i < n_cols - 1; ++i)
            {
                for (int j = i + 1; j < n_cols; ++j)
                {
                    // matrix_b.print_repr();
                    // std::cout << matrix_b.extract_element(i, j) << " " << matrix_b.extract_element(j, i) << "\n";
                    convergence_status = convergence_status
                        + std::pow(matrix_b.extract_element(i, j), 2)
                        + std::pow(matrix_b.extract_element(j, i), 2);
                    // std::cout <<"============================   " << convergence_status << ">>>>>>>>>>>>>>>>>\n\n";

                    // do the 2x2 svd.first << "    " << matrix_u.get_shape().second << "   ------------------\n\n";
        // std::cout << matrix_v.get_shape()
                    SVD2x2Decomposer<T> svd_2x2;
                    auto [c1, s1, c2, s2, d1, d2] = svd_2x2(
                        matrix_b.extract_element(i, i),
                        matrix_b.extract_element(i, j),
                        matrix_b.extract_element(j, i),
                        matrix_b.extract_element(j, j)
                    );

                    Matrix<T> test_rot = MakeDiagonal<T>()(T(1), n_rows, n_cols);
                    test_rot.set_element(matrix_b.extract_element(i, i), i, i);
                    test_rot.set_element(matrix_b.extract_element(j, j), j, j);
                    test_rot.set_element(matrix_b.extract_element(i, j), i, j);
                    test_rot.set_element(matrix_b.extract_element(j, i), j, i);
                    // test_rot.print_repr();
                    // std::cout<<matrix_b.extract_element(i, i)<<" "<<matrix_b.extract_element(i, j)<<"\n"<<matrix_b.extract_element(j, i)<<" "<<matrix_b.extract_element(j, j)<<"\n\n";

                    // T c11, s11, c21, s21, d11, d21;
                    // Svd2x2Helper(test_rot, c11, s11, c21, s21, d11, d21);

                    // T check_1 = c1 + c2 + s1 + s2 + d1 + d2;
                    // T check_2 = c11 + c21 + s11 + s21 + d11 + d21;
                    // std::cout << "\n\n>>>>>>>>>>     " << check_1 - check_2 << "     <<<<<<<<<<\n\n\n\n";

                    // Matrix<T> test_rot_v1 = MakeDiagonal<T>()(T(1), 3, 1);
                    // test_rot_v1.set_element(matrix_b.extract_element(i, i), i, i);
                    // test_rot_v1.set_element(matrix_b.extract_element(j, i), j, i);

                    // Matrix<T> test_rot_v2 = MakeDiagonal<T>()(T(1), 3, 1);
                    // test_rot_v2.set_element(matrix_b.extract_element(i, j), i, i);
                    // test_rot_v2.set_element(matrix_b.extract_element(j, j), j, i);

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

                    Matrix<T> matrix_singular_values = MakeDiagonal<T>()(T(1), n_rows, n_cols);
                    matrix_singular_values.set_element(d1, i, i);
                    matrix_singular_values.set_element(d2, j, j);

                    // matrix_left_rot.transpose().multiply(matrix_singular_values).multiply(matrix_right_rot).print_repr();
                    // matrix_left_rot.multiply(test_rot).multiply(matrix_right_rot.transpose()).print_repr();

                    // matrix_left_rot.multiply(test_rot_v1).print_repr();
                    // matrix_left_rot.multiply(test_rot_v2).print_repr();

                    // test_rot_v1.transpose().multiply(matrix_right_rot.transpose()).print_repr();
                    // test_rot_v2.transpose().multiply(matrix_right_rot.transpose()).print_repr();

                    // matrix_left_rot.multiply(test_rot).multiply(matrix_right_rot).print_repr();

                    // matrix_b.print_repr();
                    matrix_b = matrix_left_rot.multiply(matrix_b).multiply(matrix_right_rot.transpose());
                    // matrix_b.set_element(d1, i, i);
                    // matrix_b.set_element(d2, j, j);
                    // matrix_b.set_element(T(0), i, j);
                    // matrix_b.set_element(T(0), j, i);
                    // matrix_b.print_repr();
                    // matrix_singular_values.print_repr();
                    // std::cout << d1 << " " << d2 << "<<<<<<<<<<<<<<<<<<<<<<<\n";
                    // matrix_left_rot.print_repr();
                    // matrix_right_rot.print_repr();
                    // matrix_u = matrix_u.multiply(matrix_left_rot);
                    matrix_u = matrix_left_rot.multiply(matrix_u);
                    matrix_v = matrix_right_rot.multiply(matrix_v);
                    // matrix_v = matrix_right_rot.multiply(matrix_v);

                    // matrix_u.print_repr();
                    // matrix_v.print_repr();
                    // matrix_u.multiply(matrix_b).multiply(matrix_v.transpose()).print_repr();

                    counter++;
                }
            }
        } while (convergence_status > tolerance);
        matrix_s = MakeDiagonal<T>()(matrix_b);
        if (transpose == false)
        {
            matrix_u = matrix_u.transpose();
        }
        else
        {
            // std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
            matrix_s = matrix_s.transpose();
            matrix_v = matrix_v.transpose();
            std::swap(matrix_u, matrix_v);
        }
        // std::cout << matrix_u.get_shape().first << "    " << matrix_u.get_shape().second << "   ------------------\n\n";
        // std::cout << matrix_v.get_shape().first << "    " << matrix_v.get_shape().second << "   ------------------\n\n";
        matrix_b.print_repr();
        matrix_s.print_repr();
        matrix_u.print_repr();
        matrix_v.print_repr();
        std::cout << "Number of iterations: " << counter << "\n";
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
            return std::tuple{ x, y, z, s2, c2 };
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
        return std::tuple{ x, y, z, s2, c2 };
    }
};

/**
 * @brief Helper functor that calculates the SVD decomposition of 2x2 matrix.
 * Accepts and returns raw values, not a matrix.
 *
 * Follows this SO answer with minor modifications:
 * https://scicomp.stackexchange.com/a/28506/36712
 */
template<Number T>
class SVD2x2Decomposer {
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