#pragma once
#include "eigendecomposition.hpp"
#include "svd_decomposition.hpp"

/**
 * @brief Inverts a matrix.
 * Note: currently implemented only for symmetric eigendecomposable matrices.
 */
template <Number T>
class MatrixInverter {
   private:
    Matrix<T> invert_diagonal(Matrix<T> matrix)  // creates a copy
    {
        int n_rows = matrix.get_shape().first;
        int n_cols = matrix.get_shape().second;
        int n_iter = (n_rows < n_cols) ? n_rows : n_cols;
        for (int i = 0; i < n_iter; ++i) {
            T old_el = matrix.extract_element(i, i);
            if (old_el != T(0)) {
                matrix.set_element(1 / old_el, i, i);
            }
        }
        return matrix;
    }

   public:
    Matrix<T> operator()(const Matrix<T> &matrix, bool pseudo) {
        Matrix<T> out;
        if (matrix.is_diagonal()) {
            out = invert_diagonal(matrix);
        }
        if (pseudo == true) {
            SVDDecomposer<T> svd;
            SVDDecomposition svd_output = svd(matrix);
            out =
                svd_output.matrix_v.transpose()
                    .multiply(invert_diagonal(svd_output.matrix_s).transpose())
                    .multiply(svd_output.matrix_u.transpose());
        } else {
            EigenDecomposer<T> eigendecomposer;
            Eigendecomposition<T> eigendecomposition_output =
                eigendecomposer(matrix);
            Matrix<T> eigenvalues_inverse =
                invert_diagonal(eigendecomposition_output.eigenvalues);
            out = eigendecomposition_output.eigenvectors
                      .multiply(eigenvalues_inverse)
                      .multiply(
                          eigendecomposition_output.eigenvectors.transpose());
        }
        return out;
    }
};