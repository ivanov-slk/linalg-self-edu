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

TEST(MatrixFactoryTests, MakeSameElement)
{
    Matrix<float> testable = MakeSameElement<float>()(1.15, 2, 3);
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1.15, 1.15, 1.15},
            {1.15, 1.15, 1.15}}};
    ASSERT_EQ(testable, correct);
}

TEST(MatrixFactoryTests, MakeSameElementEmpty)
{
    Matrix<float> test_input;
    Matrix<float> testable = MakeDiagonal<float>()(test_input);
    Matrix<float> correct;
    ASSERT_EQ(testable, correct);
}

TEST(MatrixFactoryTests, FlattenVectorOfMatrices)
{
    Matrix<float> mat1 = MakeSameElement<float>()(1.11, 3, 2);
    Matrix<float> mat2 = MakeSameElement<float>()(2.22, 3, 5);
    Matrix<float> mat3 = MakeSameElement<float>()(3.33, 2, 3);
    Matrix<float> mat4 = MakeSameElement<float>()(4.44, 2, 4);
    std::vector<std::vector<Matrix<float>>> input_vector{
        {mat1, mat2},
        {mat3, mat4}};
    Matrix<float> testable = FlattenVectorOfMatrices<float>()(input_vector);
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1.11, 1.11, 2.22, 2.22, 2.22, 2.22, 2.22},
            {1.11, 1.11, 2.22, 2.22, 2.22, 2.22, 2.22},
            {1.11, 1.11, 2.22, 2.22, 2.22, 2.22, 2.22},
            {3.33, 3.33, 3.33, 4.44, 4.44, 4.44, 4.44},
            {3.33, 3.33, 3.33, 4.44, 4.44, 4.44, 4.44}}};
    compare_two_matrices(testable, correct);
}

TEST(MatrixFactoryTests, FlattenVectorOfMatricesEmpty)
{
    Matrix<float> mat1, mat2, mat3, mat4;
    std::vector<std::vector<Matrix<float>>> input_vector{
        {mat1, mat2},
        {mat3, mat4}};
    Matrix<float> testable = FlattenVectorOfMatrices<float>()(input_vector);
    Matrix<float> correct;
    compare_two_matrices(testable, correct);
}

TEST(MatrixFactoryTests, FlattenVectorOfMatricesThrows)
{
    Matrix<float> mat1 = MakeSameElement<float>()(1.11, 3, 2);
    Matrix<float> mat2 = MakeSameElement<float>()(2.22, 3, 5);
    Matrix<float> mat3 = MakeSameElement<float>()(3.33, 2, 3);
    Matrix<float> mat4 = MakeSameElement<float>()(4.44, 2, 3); // should be 4 to be correct
    std::vector<std::vector<Matrix<float>>> input_vector{
        {mat1, mat2},
        {mat3, mat4}};
    ASSERT_THROW(FlattenVectorOfMatrices<float>()(input_vector), BadDimensionsException);
}