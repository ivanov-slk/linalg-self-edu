#pragma once
#include "matrix_tests_utilities.hpp"

TEST(MatrixTranspositionTests, Transpose)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 4.},
            {2., 5.},
            {3., 6.}}};
    ASSERT_EQ(testable.transpose(), correct);
}

TEST(MatrixTranspositionTests, TransposeTranspose)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_EQ(testable.transpose().transpose(), testable);
}

TEST(MatrixTranspositionTests, TransposeSquare)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.},
            {7., 8., 9.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 4., 7.},
            {2., 5., 8.},
            {3., 6., 9.}}};
    ASSERT_EQ(testable.transpose(), correct);
}