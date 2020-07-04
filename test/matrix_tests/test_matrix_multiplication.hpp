#pragma once
#include "matrix_tests_utilities.hpp"

TEST(MatrixMultiplicationTests, MatrixMultiply1)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2{
        std::vector<std::vector<float>>{
            {1., 1.},
            {2., 2.},
            {3., 3.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {14., 14.},
            {32., 32.}}};
    ASSERT_EQ(mat1.multiply(mat2), correct);
}

TEST(MatrixMultiplicationTests, MatrixMultiply2)
{
    // arrange
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {51.5, 72.2},
            {48.0, 52.9},
            {8.4, 23.7}}};
    Matrix<float> mat2{
        std::vector<std::vector<float>>{
            {87.7, 12.48, 6.123},
            {12.12, 54.48, 21.789}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {5391.614, 4576.176, 1888.5003},
            {4850.748, 3481.032, 1446.5421},
            {1023.924, 1396.008, 567.8325}}};

    // act
    Matrix<float> result = mat1.multiply(mat2);

    // assert
    compare_two_matrices(result, correct);
}

TEST(MatrixMultiplicationTests, MatrixMultiplyEmpty)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {51.5, 72.2},
            {48.0, 52.9},
            {8.4, 23.7}}};
    Matrix<float> mat2;
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {51.5, 72.2},
            {48.0, 52.9},
            {8.4, 23.7}}};
    ASSERT_EQ(mat1.multiply(mat2), correct);
}

TEST(MatrixMultiplicationTests, MatrixMultiplyThrows)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {51.5, 72.2},
            {48.0, 52.9},
            {8.4, 23.7}}};
    Matrix<float> mat2{
        std::vector<std::vector<float>>{
            {1., 2.},
            {3., 4.},
            {5., 6.}}};
    ASSERT_THROW(mat1.multiply(mat2), BadDimensionsException);
}

TEST(MatrixMultiplicationTests, MatrixMultiplyTranspose)
{
    Matrix<float> a{std::vector<std::vector<float>>{
        {1.2, 3.4, -5.7},
        {-5.3, 8.7, 4.127}}};
    Matrix<float> b{std::vector<std::vector<float>>{
        {34.5, 234.34},
        {876.43, -5.1243},
        {-675.234, 54.2}}};
    Matrix<float> abt = a.multiply(b).transpose();
    Matrix<float> atbt = b.transpose().multiply(a.transpose());
    compare_two_matrices(abt, atbt);
}