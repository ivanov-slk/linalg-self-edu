#pragma once
#include "matrix_tests_utilities.hpp"

TEST(MatrixInversionTests, Inversion1)
{
    Matrix<double> input_matrix{
        std::vector<std::vector<double>>{
            {1., 7., 3.},
            {7., 4., -5.},
            {3., -5., 6.}}};
    // most of these are kind of wrong, according to numpy/tensorflow
    Matrix<double> correct{
        std::vector<std::vector<double>>{
            {0.0018513643, 0.10535964, 0.086877048},
            {0.10535964, 0.0055443528, -0.048061009},
            {0.086877048, -0.048061009, 0.083177298}}};
    compare_two_matrices(correct, MatrixInverter<double>()(input_matrix));
}

TEST(MatrixInversionTests, Inversion2)
{
    Matrix<double> input_matrix{
        std::vector<std::vector<double>>{
            {52, 30, 49, 28},
            {30, 50, 8, 44},
            {49, 8, 46, 16},
            {28, 44, 16, 22}}};
    Matrix<double> correct{
        std::vector<std::vector<double>>{
            {-0.14614309, 0.0160122, 0.13296903, 0.05727115},
            {0.0160122, -0.02001525, -0.0273224, 0.03952218},
            {0.13296903, -0.0273224, -0.10078931, -0.04128719},
            {0.05727115, 0.03952218, -0.04128719, -0.07645331}}};

    compare_two_matrices(correct, MatrixInverter<double>()(input_matrix));
}
TEST(MatrixInversionTests, InversionThrows)
{
    Matrix<double> input_matrix{
        std::vector<std::vector<double>>{
            {0.70000, 0.70711},
            {0.70001, 0.70711}}};
    ASSERT_THROW(MatrixInverter<double>()(input_matrix), BadMatrixPropertiesException);
}