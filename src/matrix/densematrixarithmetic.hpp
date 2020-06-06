#pragma once
#include "arithmetic.hpp"
#include "../customconcepts.hpp"
#include "matrix.cpp"

/**
 * Implements basic arithmetic operations on a matrix object.
 */
template <Number T>
class DenseMatrixArithmetic
{
    std::vector<std::vector<T>> add(const std::vector<std::vector<T>> &lhs,
                                    const std::vector<std::vector<T>> &rhs)
    {
        std::vector<std::vector<T>> result{{1}};
        return result;
    }

    // IMatrix<T> subtract(IMatrix<T> rhs)
    // {
    //     return 1;
    // }

    // IMatrix<T> multiply(IMatrix<T> rhs)
    // {
    //     return 1;
    // }

    // IMatrix<T> divide(IMatrix<T> rhs)
    // {
    //     return 1;
    // }
};
