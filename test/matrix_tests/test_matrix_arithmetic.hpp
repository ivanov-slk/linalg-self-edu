#pragma once
#include "matrix_tests_utilities.hpp"

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

TEST(MatrixTests, AddScalarReturnsCorrect)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {2., 3., 4.},
            {5., 6., 7.}}};
    ASSERT_EQ(mat1.add(1.), correct);
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

TEST(MatrixTests, SubtractScalarReturnsCorrect)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {0., 1., 2.},
            {3., 4., 5.}}};
    ASSERT_EQ(mat1.subtract(1.), correct);
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

TEST(MatrixTests, ElementMultiplyScalarReturnsCorrect)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {2., 4., 6.},
            {8., 10., 12.}}};
    ASSERT_EQ(mat1.el_multiply(2.), correct);
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

TEST(MatrixTests, DivideScalarReturnsCorrect)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {0.5, 1., 1.5},
            {2., 2.5, 3.}}};
    ASSERT_EQ(mat1.el_divide(2.), correct);
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