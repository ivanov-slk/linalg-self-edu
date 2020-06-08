#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <concepts>

#include "../customconcepts.hpp"
#include "../exceptions.hpp"

/**
 * @brief A matrix.
 * 
 * Supports common matrix operations like:
 * - matrix multiplication;
 * - transposition;
 * - element-wise multiplication;
 * - addition / subtraction;
 * - inversion;
 * - etc.
 */
template <Number T, template <Number U> class C>
requires MatrixRepresentation<C<T>> class Matrix
/**
 * Development notes:
 * The matrix class provides a relatively high-level interface for
 * working with matrices. It does not depend on the exact representation
 * of the matrix at hand. The representation is handled via a separate
 * representation object, which is templated for the purpose.
 * 
 * By idea, this should allow seamless conversion between dense matrices
 * and (the various forms of) sparse matrices by performing various common
 * operations on them. To accompolish this, the representation is templated
 * as a concept and supplied via a template argument. The actual matrix data
 * is supplied via the constructor and passed on to the representation.
 * 
 * One can work with the representation alone, but this would make him
 * dependent on the concrete representation (dense, sparse) of the matrix.
 * This class works to remove this issue.
 * 
 * The downside is that this class should provide a separate constructor overload
 * for each implemented matrix representation. This makes the adding of new matrix
 * representation a bit cumbersome and not quite SOLID (at far as the Open/Closed
 * principle is concerned, at least). 
 * In order to add new matrix representation, one has to implement a matrix representation
 * following the MatrixRepresentation concept (fair enough) and adding one or more 
 * constructor overloads (not optimal) to this class so that it can work with the
 * new representation.
 * 
 * An alternative would be to create a separate raw representation concept and supply
 * it as a template argument as well (this would fit into only one constructor), but
 * requires from the client code to work with three template arguments (not optimal
 * either).
 */
{
private:
    C<T> representation;

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