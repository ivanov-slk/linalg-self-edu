#pragma once
#include "eigendecomposition.hpp"
#include "svd_decomposition.hpp"

/**
 * @brief Inverts a matrix.
 * Note: currently implemented only for symmetric eigendecomposable matrices.
 */
template <Number T>
class MatrixInverter
{
private:
    Matrix<T> invert_diagonal(Matrix<T> matrix) // creates a copy
    {
        int n_rows = matrix.get_shape().first;
        int n_cols = matrix.get_shape().second;
        int n_iter = (n_rows < n_cols) ? n_rows : n_cols;
        for (int i = 0; i < n_iter; ++i)
        {
            T old_el = matrix.extract_element(i, i);
            if (old_el != T(0))
            {
                matrix.set_element(1 / old_el, i, i);
            }
        }
        return matrix;
    }

public:
    Matrix<T> operator()(const Matrix<T> &matrix, bool pseudo)
    {
        Matrix<T> out;
        if (matrix.is_diagonal())
        {
            out = invert_diagonal(matrix);
        }
        if (pseudo == true)
        {
            SVDDecomposer<T> svd;
            svd(matrix);
            svd.matrix_u.print_repr();
            svd.matrix_s.print_repr();
            svd.matrix_v.print_repr();
            out = svd.matrix_v.transpose().multiply(invert_diagonal(svd.matrix_s).transpose()).multiply(svd.matrix_u.transpose());
        }
        else
        {
            EigenDecomposer<T> eigendecomposer;
            eigendecomposer(matrix);
            Matrix<T> eigenvalues_inverse = invert_diagonal(eigendecomposer.eigenvalues);
            out = eigendecomposer.eigenvectors.multiply(eigenvalues_inverse)
                      .multiply(eigendecomposer.eigenvectors.transpose());
        }
        return out;
    }
};