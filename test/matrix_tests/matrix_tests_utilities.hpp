#pragma once
#include "../../src/customconcepts.hpp"
#include "../../src/exceptions.hpp"
#include "../../src/matrix/eigendecomposition.hpp"
#include "../../src/matrix/inversion.hpp"
#include "../../src/matrix/matrix.hpp"
#include "../../src/matrix/matrix_factory.hpp"
#include "../../src/matrix/qr_decomposition.hpp"
#include "../../src/matrix/svd_decomposition.hpp"
#include <cmath>
#include <gtest/gtest.h>

template <Number T> void compare_two_matrices(const Matrix<T> &first, const Matrix<T> &second)
{
    ASSERT_EQ(first.get_shape(), second.get_shape());
    std::vector<std::vector<T>> res_data = first.get_data();
    std::vector<std::vector<T>> cor_data = second.get_data();
    for (typename std::vector<T>::size_type i = 0; i < res_data.size(); ++i)
    {
        for (typename std::vector<T>::size_type j = 0; j < res_data[0].size(); ++j)
        {
            T a = res_data[i][j];
            T b = cor_data[i][j];
            ASSERT_FLOAT_EQ(a, b);
        }
    }
}