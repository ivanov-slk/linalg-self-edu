#pragma once

#include "../customconcepts.hpp"

/**
 * @brief Makes a diagonal matrix.
 */
template <Number T>
class MakeDiagonal
    // Most of the code here is duplicated. Consider refactoring to lambda or something.
{
public:
    /**
     * @brief Makes a diagonal matrix with a single element on the diagonal.
     */
    Matrix<T> operator()(T diag_element, int n_rows, int n_cols)
    {
        std::vector<std::vector<T>> out;
        for (int i = 0; i < n_rows; ++i)
        {
            std::vector<T> temp_row;
            for (int j = 0; j < n_cols; ++j)
            {
                if (i == j)
                {
                    temp_row.push_back(diag_element);
                }
                else
                {
                    temp_row.push_back(T(0));
                }
            }
            out.push_back(temp_row);
        }
        return Matrix<T>{out};
    }

    /**
     * @brief Makes a diagonal matrix from a matrix.
     *
     * If the matrix is a vector (n x 1 or 1 x n), the result is a square matrix with the vector's
     * elements on the main diagonal.
     *
     * If the matrix is not a vector, a new matrix is returned,
     * where all off-(main)-diagonal entries are 0-s. If the matrix is not square, the "main diagonal"
     * is assumed to be the set of elements with i=j for "i" the row index and "j" the column index.
     */
    Matrix<T> operator()(const Matrix<T> &vector)
    {
        std::vector<std::vector<T>> out;
        int n_rows = vector.get_shape().first;
        int n_cols = vector.get_shape().second;

        int out_rows = (n_rows > 1) ? n_rows : n_cols;
        int out_cols = (n_cols > 1) ? n_cols : n_rows;

        for (int i = 0; i < out_rows; ++i)
        {
            std::vector<T> temp_row;
            for (int j = 0; j < out_cols; ++j)
            {
                if (i == j)
                {
                    // formally, adds only a constant to the overall complexity...
                    if (n_rows == 1)
                    {
                        temp_row.push_back(vector.extract_element(0, j));
                    }
                    else if (n_cols == 1)
                    {
                        temp_row.push_back(vector.extract_element(i, 0));
                    }
                    else
                    {
                        temp_row.push_back(vector.extract_element(i, j));
                    }
                }
                else
                {
                    temp_row.push_back(T(0));
                }
            }
            out.push_back(temp_row);
        }
        return Matrix<T>{out};
    }
};

/**
 * @brief Makes a matrix with all elements equal to a given value.
 */
template <Number T>
class MakeSameElement
{
public:
    Matrix<T> operator()(T value, int n_rows, int n_cols)
    {
        std::vector<std::vector<T>> out;
        for (int i = 0; i < n_rows; ++i)
        {
            std::vector<T> temp_row;
            for (int j = 0; j < n_cols; ++j)
            {
                temp_row.push_back(value);
            }
            out.push_back(temp_row);
        }
        return Matrix<T>{out};
    }
};

/**
 * @brief Makes a matrix from a vector of matrices.
 *
 * This is implemented for the QR decomposition, so consider generalizing/refactoring it.
 * And consider making the implementation more efficient, since now is sort of terrible.
 */
template <Number T>
class FlattenVectorOfMatrices
{
public:
    Matrix<T> operator()(const std::vector<std::vector<Matrix<T>>> &matrices)
    {
        // Currently, the checks that the inputs can actually produce a valid matrix are delegated
        // to the Matrix constructor at the end of the method. This is fine for small matrices, but
        // for large matrices it would be better to throw at the beginning of the method and avoid
        // all the loops.

        std::vector<std::vector<T>> out;
        for (auto &row_of_matrices : matrices)
        {
            int n_rows = row_of_matrices.at(0).get_shape().first;
            for (int i = 0; i < n_rows; ++i)
            {
                std::vector<T> temp_row;
                for (auto &matrix : row_of_matrices)
                {
                    int n_cols = matrix.get_shape().second;
                    for (int j = 0; j < n_cols; ++j)
                    {
                        temp_row.push_back(matrix.extract_element(i, j));
                    }
                }
                out.push_back(temp_row);
            }
        }
        return Matrix<T>{out};
    }
};