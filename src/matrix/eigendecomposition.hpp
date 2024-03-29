#pragma once
#include "matrix.hpp"
#include "qr_decomposition.hpp"

template <Number T>
struct Eigendecomposition {
    Matrix<T> eigenvalues;
    Matrix<T> eigenvectors;
};

/**
 * @brief Decomposes a matrix in a matrix of eigenvectors and diagonal matrix of
 * eigenvalues.
 *
 * The implementation is *slow*. Seriously consider refactoring it to something
 * acceptable.
 */
template <Number T>
class EigenDecomposer {
   public:
    Matrix<T> eigenvectors;
    Matrix<T> eigenvalues;
    Eigendecomposition<T> operator()(const Matrix<T> &matrix) {
        if (!matrix.is_symmetric()) {
            throw BadMatrixPropertiesException{
                "Only symmetric real matrices are supported."};
        }

        Matrix<T> loop_q = matrix;  // yes, copy...
        std::vector<Matrix<T>> loop_q_s;
        for (int i = 0; i < 3000; ++i) {
            QRDecomposer<T> qr;
            QRDecomposition<T> qr_output = qr(loop_q);
            loop_q = qr_output.matrix_r.multiply(qr_output.matrix_q);
            loop_q_s.push_back(qr_output.matrix_q);
        }
        QRDecomposer<T> qr_last;
        qr_last(loop_q);

        // calculate the eigenvectors
        for (auto &q : loop_q_s) {
            eigenvectors = eigenvectors.multiply(q);
        }

        eigenvalues = loop_q;
        // all non-diagonal entries are by theory zero, so set them up so
        int rows = eigenvalues.get_shape().first;
        int cols = eigenvalues.get_shape().second;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (j != i) {
                    eigenvalues.set_element(T(0), i, j);
                }
            }
        }
        return Eigendecomposition<T>{eigenvalues, eigenvectors};
    }
};