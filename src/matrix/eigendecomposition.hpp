#pragma once
#include "qr_decomposition.hpp"

/**
 * @brief Decomposes a matrix in a matrix of eigenvectors and diagonal matrix of eigenvalues.
 * 
 * The implementation is *slow*.
 */
template <Number T>
class EigenDecomposer
{
public:
    Matrix<T> eigenvectors;
    Matrix<T> eigenvalues;
    Matrix<T> operator()(const Matrix<T> &matrix)
    {
        if (!matrix.is_symmetric())
        {
            throw BadMatrixPropertiesException{"Only symmetric real matrices are supported."};
        }

        Matrix<T> loop_q = matrix; // yes, copy
        std::vector<Matrix<T>> loop_q_s;
        for (int i = 0; i < 3000; ++i)
        {
            QRDecomposer<T> qr;
            qr(loop_q);
            loop_q = qr.matrix_r.multiply(qr.matrix_q);
            loop_q_s.push_back(qr.matrix_q);
        }
        QRDecomposer<T> qr_last;
        qr_last(loop_q);

        // calculate the eigenvectors
        for (auto &q : loop_q_s)
        {
            eigenvectors = eigenvectors.multiply(q);
        }
        eigenvalues = qr_last.matrix_q.multiply(loop_q.multiply(qr_last.matrix_q.transpose()));
        // all non-diagonal entries are by theory zero, so set them up so
        int rows = eigenvalues.get_shape().first;
        int cols = eigenvalues.get_shape().second;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (j != i)
                {
                    eigenvalues.set_element(T(0), i, j);
                }
            }
        }
        eigenvalues.print_repr();
        eigenvectors.print_repr();
        std::vector<std::vector<T>> out;
        return Matrix<T>{out};
    }
};