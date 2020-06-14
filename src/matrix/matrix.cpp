#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <concepts>
#include <iostream>

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

        if (get_shape() != other.get_shape())
        {
            // should never get here
            throw BadDimensionsException("The two matrices must have the same shape");
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
};

template <typename T>
bool operator==(const Matrix<T> lhs, const Matrix<T> rhs)
{
    return lhs.equals(rhs);
}
