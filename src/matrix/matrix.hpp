#pragma once
#include <memory>
#include "../customconcepts.hpp"

/**
 * @brief Provides interface to common matrix operations.
 */
template <Number T>
class IMatrix
{
public:
    virtual ~IMatrix() = default;
    virtual bool empty() const = 0;
    virtual bool equals(std::unique_ptr<IMatrix<T>> other) const = 0;
    virtual std::pair<int, int> get_shape() const = 0;
    virtual std::unique_ptr<IMatrix<T>> add(std::unique_ptr<IMatrix<T>> other) = 0;
    // virtual std::unique_ptr<IMatrix<T>> subtract(std::unique_ptr<IMatrix<T>> other) = 0;
    // virtual std::unique_ptr<IMatrix<T>> multiply(std::unique_ptr<IMatrix<T>> other) = 0;
    // virtual std::unique_ptr<IMatrix<T>> divide(std::unique_ptr<IMatrix<T>> other) = 0;
};

template <Number T>
std::unique_ptr<IMatrix<T>> MakeDenseMatrix();

template <Number T> // not implemented (yet)
std::unique_ptr<IMatrix<T>> MakeSparseMatrix();