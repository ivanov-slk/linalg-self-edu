#pragma once
#include <cmath>
#include <gtest/gtest.h>
#include "../../src/matrix/matrix.hpp"
#include "../../src/exceptions.hpp"
#include "../../src/customconcepts.hpp"

// template <Number T>
void compare_two_matrices(const Matrix<float> &first, const Matrix<float> &second)
{
    std::vector<std::vector<float>> res_data = first.get_data();
    std::vector<std::vector<float>> cor_data = second.get_data();
    for (typename std::vector<float>::size_type i = 0; i < res_data.size(); ++i)
    {
        for (typename std::vector<float>::size_type j = 0; j < res_data[0].size(); ++j)
        {
            float a = res_data[i][j];
            float b = cor_data[i][j];
            ASSERT_FLOAT_EQ(a, b);
        }
    }
}