#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <concepts>
#include <iostream>
#include <cmath>

#include "../customconcepts.hpp"
#include "../exceptions.hpp"

/**
 * @brief A matrix.
 */
template <Number T>
class Matrix
{
private:
    int n_rows = 0;
    int n_cols = 0;
    std::vector<std::vector<T>> data;
    // Just as an idea, consider flattening the representation.

    Matrix<T> do_arithmetic(const Matrix<T> &other, std::function<T(T, T)> binary_op)
    {
        if (empty())
        {
            return Matrix<T>{other.data};
        }

        if (other.empty())
        {
            return Matrix<T>{data};
        }
        std::vector<std::vector<T>> out;
        out.reserve(other.data.size());
        std::transform(data.begin(),
                       data.end(),
                       other.data.begin(),
                       std::back_inserter(out),
                       [&binary_op](const std::vector<T> &x1,
                                    const std::vector<T> &x2) {
                           std::vector<T> temp;
                           std::transform(x1.begin(),
                                          x1.end(),
                                          x2.begin(),
                                          std::back_inserter(temp),
                                          binary_op);
                           return temp;
                       });

        return Matrix<T>{out};
    }

public:
    Matrix() {}
    Matrix(const std::vector<std::vector<T>> &data) : data(data)
    {
        if (data.empty())
        {
            n_rows = 0;
            n_cols = 0;
        }
        else
        {
            n_rows = data.size();
            int temp_cols = data[0].size();
            for (std::vector<T> element : data)
            {
                if (element.size() != temp_cols)
                {
                    throw BadDimensionsException("Each row must have the same number of elements.");
                }
                temp_cols = element.size();
            }
            n_cols = temp_cols;
        }
    }

    /**
     * @brief Checks if the matrix is empty.
     * @return bool true if the matrix is empty.
     */
    bool empty() const { return data.empty(); }

    /**
     * @brief Checks if two matrices are equal.
     * @param other Matrix
     * @return bool true if matrices are equal.
     * 
     * ...should hash be also implemented?
     * ...should T be used again? What about different number template and cast?
     */
    bool equals(const Matrix<T> &other) const
    {
        return data == other.data;
    }

    /**
     * @brief Get the shape of the matrix
     * 
     * @return std::pair<int, int> - `first` is the number of rows, `second` is the number of columns
     */
    std::pair<int, int> get_shape() const
    {
        return std::make_pair(n_rows, n_cols);
    }

    /**
     * @brief Get the raw data.
     */
    std::vector<std::vector<T>> get_data() const { return data; }

    /**
     * @brief Add a matrix to this.
     */
    Matrix<T> add(const Matrix<T> &other)
    {
        return do_arithmetic(other, std::plus<T>());
    }

    /**
     * @brief Subtract a matrix from this.
     */
    Matrix<T> subtract(const Matrix<T> &other)
    {
        return do_arithmetic(other, std::minus<T>());
    }

    /**
     * @brief Multiply a matrix by this elementwise.
     */
    Matrix<T> el_multiply(const Matrix<T> &other)
    {
        return do_arithmetic(other, std::multiplies<T>());
    }

    /**
     * @brief Divide this by other.
     */
    Matrix<T> el_divide(const Matrix<T> &other)
    {
        return do_arithmetic(other, std::divides<T>());
    }

    /**
     * @brief Return new transposed matrix.
     */
    Matrix<T> transpose()
    {
        // consider a better implementation...
        std::vector<std::vector<T>> out;

        for (typename std::vector<T>::size_type i = 0; i < n_cols; ++i)
        {
            std::vector<T> temp;
            for (typename std::vector<T>::size_type j = 0; j < n_rows; ++j)
            {
                temp.push_back(data[j][i]);
            }
            out.push_back(temp);
        }
        return Matrix<T>{out};
    }

    /**
     * @brief Multiplies two matrices producing new one.
     */
    Matrix<T> multiply(const Matrix<T> &other)
    {
        if (empty())
        {
            return Matrix<T>{other.data};
        }

        if (other.empty())
        {
            return Matrix<T>{data};
        }

        if (get_shape().second != other.get_shape().first)
        {
            throw BadDimensionsException("The dimensions are invalid for matrix multiplication.");
        }

        std::vector<std::vector<T>> out;

        /** 
         * Again, I don't quite like this vector subsetting...
         * Alternatively, you can _transpose_ one of the matrices, multiply element-wise
         * two columns and then std::accumulate() them.
         * 
         * Or you can just implement Strassen or similar...
         */
        for (typename std::vector<T>::size_type i = 0; i < n_rows; ++i)
        {
            std::vector<T> temp_row;
            for (typename std::vector<T>::size_type j = 0; j < n_rows; ++j)
            {
                T temp_sum = T(0);
                for (typename std::vector<T>::size_type k = 0; k < n_cols; ++k)
                {
                    temp_sum += data[i][k] * other.data[k][j];
                }
                temp_row.push_back(temp_sum);
            }
            out.push_back(temp_row);
        }
        return Matrix<T>{out};
    }

    /**
     * @brief Take the norm of the matrix.
     * 
     * Note that if the matrix has only one row / column, the vector norm is returned.
     * Otherwise, the "entrywise" norm of the whole matrix is returned. For p=2,
     * this is the Frobenius norm.
     * 
     * Check https://en.wikipedia.org/wiki/Matrix_norm#%22Entrywise%22_matrix_norms.
     */
    float norm(float p)
    {
        float temp_sum = float(0);
        for (typename std::vector<T>::size_type i = 0; i < n_rows; ++i)
        {
            for (typename std::vector<T>::size_type j = 0; j < n_cols; ++j)
            {
                // explicit casting, the norm is unlikely to be an integer
                float current_value = (float)data[i][j];
                // take absolute value (might use std::abs(), but have to manage overloads)
                // then exponentiate
                temp_sum += std::pow(((current_value < 0) ? -current_value : current_value), p);
            }
        }
        return std::pow(temp_sum, (1 / p));
    }

    /**
     * @brief Find the trace of the matrix.
     * 
     * Works only for square matrices. Otherwise returns 0.
     * ?? Is it ok to return 0? Why not raise an exception?
     */
    T trace()
    {
        if (n_rows != n_cols)
        {
            return T(0);
        }
        T temp_sum = T(0);
        for (typename std::vector<T>::size_type i = 0; i < n_rows; ++i)
        {
            temp_sum += data[i][i];
        }
        return temp_sum;
    }

    /**
     * @brief Calculates the QR decomposition of the matrix.
     * 
     * Requires that the matrix is square.
     */
    // void qr_decompose()
    // {
    //     Matrix<T> matrix_r;
    //     Matrix<T> matrix_q;
    //     for (typename std::vector<T> size_type i = 0; i < n_cols; ++i)
    //     {
    //         // I need functions to extract rows, columns, adjoint matrices
    //         // I need function overloads to do arithmetic with scalars
    //         // I need function to create identity matrix based on given rows and columns
    //         // I need function to create diagonal matrix from a vector
    //         // get unit vector from the column
    //         std::vector<std::vector<T>> col_data;
    //         for (typename std::vector<T> size_type j = 0; j < n_rows)
    //             Matrix<T> current_column;

    //         // create an identity matrix

    //         // calculate Q

    //         // resize Q

    //         // update matrix_r

    //         // update matrix_q
    //     }
    // }

    /**
     * @brief Checks if the matrix is symmetric.
     * 
     * Relies on the property that A = A^T.
     */
    bool is_symmetric()
    {
        return this->equals(transpose());
    }
};

template <typename T>
bool operator==(const Matrix<T> lhs, const Matrix<T> rhs)
{
    return lhs.equals(rhs);
}
