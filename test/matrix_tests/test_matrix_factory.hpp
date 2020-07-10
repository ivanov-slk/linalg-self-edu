#pragma once
#include "matrix_tests_utilities.hpp"
#include "../../src/matrix/matrix_factory.hpp"

TEST(MatrixFactoryTests, MakeDiagonal1)
{
    Matrix<float> testable = MakeDiagonal<float>()(1.0, 3, 3);
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0}}};
    ASSERT_EQ(testable, correct);
}

TEST(MatrixFactoryTests, MakeDiagonal2)
{
    Matrix<float> testable = MakeDiagonal<float>()(1.0, 3, 2);
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1.0, 0.0},
            {0.0, 1.0},
            {0.0, 0.0}}};
    ASSERT_EQ(testable, correct);
}