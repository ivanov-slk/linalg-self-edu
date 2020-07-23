#pragma once
#include "qr_decomposition.hpp"

/**
 * @brief Decomposes a matrix in a matrix of eigenvectors and diagonal matrix of eigenvalues.
 */
template <Number T>
class EigenDecomposer
{
public:
    Matrix<T> operator()(const Matrix<T> &matrix)
    {
        if (!matrix.is_symmetric())
        {
            throw BadMatrixPropertiesException{"Only symmetric real matrices are supported."};
        }
        std::vector<std::vector<T>> out;
        return Matrix<T>{out};
    }
};