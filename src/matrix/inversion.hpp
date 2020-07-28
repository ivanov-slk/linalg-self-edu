#pragma once
#include "eigendecomposition.hpp"

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
            T new_el = 1 / matrix.extract_element(i, i);
            matrix.set_element(new_el, i, i);
        }
        return matrix;
    }

public:
    Matrix<T> operator()(const Matrix<T> &matrix)
    {
        if (matrix.is_diagonal())
        {
            return invert_diagonal(matrix);
        }
        EigenDecomposer<T> eigendecomposer;
        eigendecomposer(matrix);
        Matrix<T> eigenvalues_inverse = invert_diagonal(eigendecomposer.eigenvalues);
        return eigendecomposer.eigenvectors.multiply(eigenvalues_inverse)
            .multiply(eigendecomposer.eigenvectors.transpose());
    }
};