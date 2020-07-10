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

TEST(MatrixFactoryTests, MakeDiagonal3)
{
    Matrix<float> test_input{
        std::vector<std::vector<float>>{
            {1.0, 3.2},
            {2.5, 4.8},
            {-5.2, 3.6}}};
    Matrix<float> testable = MakeDiagonal<float>()(test_input);
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1.0, 0.0},
            {0.0, 4.8},
            {0.0, 0.0}}};
    ASSERT_EQ(testable, correct);
}

TEST(MatrixFactoryTests, MakeDiagonal4)
{
    Matrix<float> test_input{
        std::vector<std::vector<float>>{
            {1.0, 3.2, 5.1},
            {2.5, 4.8, 2.3},
            {-5.2, 3.6, 1.3}}};
    Matrix<float> testable = MakeDiagonal<float>()(test_input);
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1.0, 0.0, 0.0},
            {0.0, 4.8, 0.0},
            {0.0, 0.0, 1.3}}};
    ASSERT_EQ(testable, correct);
}

TEST(MatrixFactoryTests, MakeDiagonalEmpty)
{
    Matrix<float> test_input;
    Matrix<float> testable = MakeDiagonal<float>()(test_input);
    Matrix<float> correct;
    ASSERT_EQ(testable, correct);
}