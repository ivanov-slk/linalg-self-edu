#pragma once
#include <ranges>
#include "matrix.hpp"

/**
 * @brief Performs a QR decomposition on a matrix.
 * 
 * Note: the results are stored as public variables (`matrix_q` and `matrix_r`).
 * Note: the implementation follows https://en.wikipedia.org/wiki/QR_decomposition#Using_Householder_reflections.
 */
template <Number T>
class QRDecomposer
{
private:
    Matrix<T> create_householder_matrix(const Matrix<T> &vector, const Matrix<T> &basis, int k)
    {
        // calculate alpha = sign(x[k])||x||
        // the first element of `vector` is the k-th of the decomposable matrix
        T sign_alpha = (vector.extract_element(k, 0) < 0) ? -1 : 1;
        T alpha = sign_alpha * vector.norm(2);

        // calculate x - alpha*e_i and make it unit
        Matrix<T> unit_vector = vector.subtract(basis.el_multiply(alpha));
        unit_vector = unit_vector.el_divide(unit_vector.norm(2));

        // calculate the Householder matrix
        int householder_rows = vector.get_shape().first;
        Matrix<T> basis_matrix = MakeDiagonal<T>()(T(1), householder_rows, householder_rows); // square
        Matrix<T> householder_matrix = basis_matrix.subtract(
            unit_vector.multiply(
                           unit_vector.transpose())
                .el_multiply(2));
        return householder_matrix;
    }

public:
    Matrix<T> matrix_q;
    Matrix<T> matrix_r;
    void operator()(const Matrix<T> &matrix)
    {
        // check dimensions and number of iterations
        int n_rows = matrix.get_shape().first;
        int n_cols = matrix.get_shape().second;
        int n_iter = ((n_rows - 1) < n_cols) ? n_rows - 1 : n_cols;
        // create identity matrix
        Matrix<T> identity = MakeDiagonal<T>()(T(1), n_rows, n_cols);
        std::vector<Matrix<T>> matrices_q;
        Matrix<T> q_i_multiply_input = matrix; // copy (!!!), initialize

        // loop over the above number
        for (int i = 0; i < n_iter; ++i)
        {
            // extract the two input vectors
            // calculate a Householder matrix
            Matrix<T> q_i = create_householder_matrix(
                q_i_multiply_input.extract_submatrix(i, i).extract_column(0),
                identity.extract_submatrix(i, i).extract_column(0),
                i);
            // q_i = q_i.multiply(q_i_resized.extract_submatrix(i, i));
            // resize the Householder matrix to the input matrix's dimensions
            Matrix<T> upper_identity = MakeDiagonal<T>()(T(1), i, i);
            Matrix<T> upper_zeroes = MakeSameElement<T>()(T(0), i, n_cols - i);
            Matrix<T> lower_zeroes = MakeSameElement<T>()(T(0), n_rows - i, i);
            std::vector<std::vector<Matrix<T>>> resize_placeholder{
                {upper_identity, upper_zeroes},
                {lower_zeroes, q_i}};
            Matrix<T> q_i_resized = FlattenVectorOfMatrices<T>()(resize_placeholder);
            // store the Householder matrix
            q_i_multiply_input = q_i_resized.multiply(q_i_multiply_input);
            matrices_q.push_back(q_i_resized);
        }
        // use all stored Householder matrices to calculate Q and R
        // for (auto &matrix : std::ranges::views::reverse(matrices_q))
        // {
        //     matrix_r = matrix_r.multiply(matrix);
        // }
        matrix_r = q_i_multiply_input;
        for (auto &matrix : matrices_q)
        {
            matrix_q = matrix_q.transpose().multiply(matrix.transpose());
        }
    }
};