#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <concepts>

#include "../customconcepts.hpp"
#include "../exceptions.hpp"

/**
 * @brief A matrix object. Efficiency is not important (at the moment).
 * 
 * Supports common matrix operations like:
 * - matrix multiplication;
 * - transposition;
 * - element-wise multiplication;
 * - addition / subtraction;
 * - inversion;
 * - etc.
 * 
 * 
 */
// template <Number T, MatrixRepresentation<T> R>
template <typename T, template <typename> typename C>
requires Number<T> &&MatrixRepresentation<C<T>>
    // template <Number T, MatrixRepresentation R>
    class Matrix
{
private:
    int n_rows = 0; // These are set in the constructor currently, which requires them to be
    int n_cols = 0; // non-const. At least the data is const... but in any case this is not the best.
    const C<T> representation;

public:
    Matrix() {}
    Matrix(const std::vector<std::vector<T>> &data) : representation(data)
    {
    }

    /**
     * @brief Checks if the matrix is empty.
     * @return bool true if the matrix is empty.
     */
    bool empty() const
    {
        return representation.empty();
    }

    /**
     * @brief Checks if two matrices are equal.
     * @param other Matrix
     * @return bool true if matrices are equal.
     * 
     * ...should hash be also implemented?
     */
    // bool equals(const Matrix<Number T, MatrixRepresentation R> &other) const
    // {
    //     if (get_shape() != other.get_shape())
    //     {
    //         return false;
    //     }
    //     return data == other.data;
    // }

    /**
     * @brief Get the shape of the matrix
     * 
     * @return std::pair<int, int> - `first` is the number of rows, `second` is the number of columns
     */
    std::pair<int, int> get_shape() const
    {
        return std::make_pair(n_rows, n_cols);
    }

    // Matrix<T> add(const Matrix<T> &other)
    // {
    //     if (empty())
    //     {
    //         return Matrix<T>{other.data};
    //     }

    //     if (other.empty())
    //     {
    //         return Matrix<T>{data};
    //     }

    //     if (get_shape() != other.get_shape())
    //     {
    //         throw BadDimensionsException("The two matrices must have the same shape");
    //     }

    //     std::vector<std::vector<T>> out;
    //     out.reserve(other.data.size());
    //     for (std::vector<T> element : other.data)
    //     {
    //         std::transform(element.begin(),
    //                        element.end(),
    //                        out.begin(),
    //                        std::back_inserter(out),
    //                        std::plus<T>());
    //     }

    //     return Matrix<T>{out};
    // }
};

// template <typename T>
// bool operator==(const Matrix<T, R> lhs, const Matrix<T, U> rhs)
// {
//     return lhs.equals(rhs);
// }

// template <Number T>
// Matrix<T> MakeDenseMatrix(const std::vector<std::vector<T>> &data)
// {
//     auto out = std::make_unique<Matrix<T, DenseMatrixArithmetic<T>>>(data);
//     return out;
// };