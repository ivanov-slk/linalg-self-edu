#pragma once
#include "matrix_tests_utilities.hpp"

TEST(MatrixTests, Empty)
{
    std::vector<std::vector<int>> data;
    Matrix<int> testable{data};
    ASSERT_TRUE(testable.empty());
}

TEST(MatrixTests, NotEmpty)
{
    std::vector<std::vector<int>> data{
        {1, 2, 3},
        {4, 5, 6}};
    Matrix<int> testable{data};
    ASSERT_TRUE(!testable.empty());
}

TEST(MatrixTests, CorrectShape)
{
    std::vector<std::vector<int>> data{
        {1, 2, 3},
        {4, 5, 6}};
    Matrix<int> testable{data};
    ASSERT_EQ(std::make_pair(2, 3), testable.get_shape());
}

TEST(MatrixTests, CorrectShapeEmpty)
{
    std::vector<std::vector<int>> data;
    Matrix<int> testable{data};
    ASSERT_EQ(std::make_pair(0, 0), testable.get_shape());
}

TEST(MatrixTests, ThrowsBadShape)
{
    std::vector<std::vector<int>> data{
        {1, 2, 3},
        {4, 5}};
    ASSERT_THROW((Matrix<int>{data}), BadDimensionsException);
}

TEST(MatrixTests, Equal)
{
    std::vector<std::vector<int>> data1{
        {1, 2, 3},
        {4, 5, 6}};
    std::vector<std::vector<int>> data2{
        {1, 2, 3},
        {4, 5, 6}};
    Matrix<int> testable1{data1};
    Matrix<int> testable2{data2};
    ASSERT_TRUE(testable1.equals(testable2));
}

TEST(MatrixTests, NotEqual)
{
    std::vector<std::vector<int>> data1{
        {1, 2, 3},
        {4, 5, 6}};
    std::vector<std::vector<int>> data2{
        {1, 5, 3},
        {4, 2, 6}};
    Matrix<int> testable1{data1};
    Matrix<int> testable2{data2};
    ASSERT_FALSE(testable1.equals(testable2));
}