#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <concepts>

#include "../customconcepts.hpp"
#include "../exceptions.hpp"

/**
 * @brief A matrix.
 */
template <typename T, template <class U> class R>
requires MatrixRepresentation<T, R> class Matrix
{
private:
    R<T> representation;

public:
    Matrix() {}
    Matrix(const std::vector<std::vector<T>> &data) : representation(data) {}
    // add more constructor overloads here

    /**
     * @brief Checks if the matrix is empty.
     * @return bool true if the matrix is empty.
     */
    bool empty()
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
    // bool equals(const Matrix<T, C<T>> &other)
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
    std::pair<int, int> get_shape()
    {
        return representation.get_shape();
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