#pragma once
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
    Matrix<T> create_householder_matrix(const Matrix<T> &vector) {}

public:
    Matrix<T> matrix_q;
    Matrix<T> matrix_r;
    void operator()(const Matrix<T> &matrix)
    {
        // check dimensions and number of iterations
        int n_rows = matrix.get_shape().first;
        int n_cols = matrix.get_shape().second;
        int n_iter = (n_rows - 1 > n_cols) ? n_rows : n_cols;
        // create identity matrix
        Matrix<T> identity = MakeDiagonal<T>()(T(1), n_rows, n_cols);

        // loop over the above number
        // extract the two input vectors
        // calculate a Householder matrix
        // resize the Householder matrix to the input matrix's dimensions
        // store the Householder matrix

        // use all stored Householder matrices to calculate Q and R
        // store the results as public variables
    }
};
