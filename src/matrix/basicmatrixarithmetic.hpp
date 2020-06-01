#include "arithmetic.hpp"
#include "customconcepts.hpp"
#include "matrix.cpp"

/**
 * Implements basic arithmetic operations on a matrix object.
 */
template <Number T>
class BasicMatrixArithmetic : public ArithmeticInterface<Matrix<T>>
{
    Matrix<T> add(Matrix<T> rhs)
    {
        return 1;
    }

    Matrix<T> subtract(Matrix<T> rhs)
    {
        return 1;
    }

    Matrix<T> multiply(Matrix<T> rhs)
    {
        return 1;
    }

    Matrix<T> divide(Matrix<T> rhs)
    {
        return 1;
    }
};