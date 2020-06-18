#include <gtest/gtest.h>
#include "../src/matrix/matrix.cpp"
#include "../src/exceptions.hpp"

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

TEST(MatrixTests, AddReturnsCorrect)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2{
        std::vector<std::vector<float>>{
            {1., 1., 1.},
            {2., 2., 2.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {2., 3., 4.},
            {6., 7., 8.}}};
    ASSERT_EQ(mat1.add(mat2), correct);
}

TEST(MatrixTests, AddReturnsSame)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2;
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_EQ(mat1.add(mat2), correct);
}

// TEST(MatrixTests, AddThrowsDimensionMismatch)
// {
//     Matrix<float> mat1{
//         std::vector<std::vector<float>>{
//             {1., 2., 3.},
//             {4., 5., 6.}}};
//     Matrix<float> mat2{
//         std::vector<std::vector<float>>{
//             {1., 1., 1.},
//             {2., 2.}}};
//     ASSERT_THROW(mat1.add(mat2), BadDimensionsException);
//     // currently impossible, because it will throw on construction of the second matrix
//     // keeping this test for reference though
// }

TEST(MatrixTests, SubtractReturnsCorrect)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2{
        std::vector<std::vector<float>>{
            {1., 1., 1.},
            {2., 2., 2.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {0., 1., 2.},
            {2., 3., 4.}}};
    ASSERT_EQ(mat1.subtract(mat2), correct);
}

TEST(MatrixTests, SubtractReturnsSame)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2;
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_EQ(mat1.subtract(mat2), correct);
}

TEST(MatrixTests, ElementMultiplyReturnsCorrect)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2{
        std::vector<std::vector<float>>{
            {1., 1., 1.},
            {2., 2., 2.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {8., 10., 12.}}};
    ASSERT_EQ(mat1.el_multiply(mat2), correct);
}

TEST(MatrixTests, ElementMultiplyReturnsSame)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2;
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_EQ(mat1.el_multiply(mat2), correct);
}

TEST(MatrixTests, DivideReturnsCorrect)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2{
        std::vector<std::vector<float>>{
            {1., 1., 1.},
            {2., 2., 2.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {2., 2.5, 3.}}};
    ASSERT_EQ(mat1.el_divide(mat2), correct);
}

TEST(MatrixTests, DivideReturnsSame)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2;
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_EQ(mat1.el_divide(mat2), correct);
}

TEST(MatrixTests, Transpose)
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

TEST(MatrixTests, TransposeTranspose)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_EQ(testable.transpose().transpose(), testable);
}

TEST(MatrixTests, TransposeSquare)
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