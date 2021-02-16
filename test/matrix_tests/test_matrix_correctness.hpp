#pragma once
#include "matrix_tests_utilities.hpp"

TEST(MatrixCorrectnessTests, Empty)
{
    std::vector<std::vector<int>> data;
    Matrix<int> testable{data};
    ASSERT_TRUE(testable.empty());
}

TEST(MatrixCorrectnessTests, NotEmpty)
{
    std::vector<std::vector<int>> data{
        {1, 2, 3},
        {4, 5, 6}};
    Matrix<int> testable{data};
    ASSERT_TRUE(!testable.empty());
}

TEST(MatrixCorrectnessTests, CorrectShape)
{
    std::vector<std::vector<int>> data{
        {1, 2, 3},
        {4, 5, 6}};
    Matrix<int> testable{data};
    ASSERT_EQ(std::make_pair(2, 3), testable.get_shape());
}

TEST(MatrixCorrectnessTests, CorrectShapeEmpty)
{
    std::vector<std::vector<int>> data;
    Matrix<int> testable{data};
    ASSERT_EQ(std::make_pair(0, 0), testable.get_shape());
}

TEST(MatrixCorrectnessTests, ThrowsBadShape)
{
    std::vector<std::vector<int>> data{
        {1, 2, 3},
        {4, 5}};
    ASSERT_THROW((Matrix<int>{data}), BadDimensionsException);
}

TEST(MatrixCorrectnessTests, Equal)
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

TEST(MatrixCorrectnessTests, NotEqual)
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

TEST(MatrixCorrectnessTests, SetElement)
{
    std::vector<std::vector<int>> data{
        {1, 2, 3},
        {4, 5, 6}};
    Matrix<int> testable{data};
    testable.set_element(-1000, 1, 1);
    Matrix<int> correct{
        std::vector<std::vector<int>>{
            {1, 2, 3},
            {4, -1000, 6}}};
    ASSERT_EQ(testable, correct);
}

TEST(MatrixCorrectnessTests, SetElementThrows)
{
    std::vector<std::vector<int>> data{
        {1, 2, 3},
        {4, 5, 6}};
    Matrix<int> testable{data};
    ASSERT_THROW(testable.set_element(-1000, 10, 1), BadDimensionsException);
}