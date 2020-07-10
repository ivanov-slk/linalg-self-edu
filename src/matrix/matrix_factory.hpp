#pragma once

#include "../customconcepts.hpp"

/**
 * @brief Makes a diagonal matrix.
 */
template <Number T>
class MakeDiagonal
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

        for (int i = 0; i < n_rows; ++i)
        {
            std::vector<T> temp_row;
            for (int j = 0; j < n_cols; ++j)
            {
                if (i == j)
                {
                    temp_row.push_back(vector.extract_element(i, j));
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