#pragma once
#include "matrix_tests_utilities.hpp"

TEST(EigendecompositionTests, EigendecompositionThrows)
{
    Matrix<double> input_matrix{
        std::vector<std::vector<double>>{
            {0.70000, 0.70711},
            {0.70001, 0.70711}}};
    EigenDecomposer<double> testable;
    ASSERT_THROW(testable(input_matrix), BadMatrixPropertiesException);
}

TEST(EigendecompositionTests, Eigendecomposition1)
{
    // arrange
    Matrix<double> input_matrix{
        std::vector<std::vector<double>>{
            {1., 7., 3.},
            {7., 4., -5.},
            {3., -5., 6.}}};
    EigenDecomposer<double> testable;
    Matrix<double> correct_vec{
        std::vector<std::vector<double>>{
            {0.36954564, -0.62879236, -0.68414629}, // tensorflow and numpy have different signs
            {0.75724338, -0.2229199, 0.613913},
            {-0.53853365, -0.74493414, 0.3937698}}};
    Matrix<double> correct_val{
        std::vector<std::vector<double>>{
            {10.97198268, 0., 0.},
            {0., 7.03594585, 0.},
            {0., 0., -7.00792852}}};

    // act
    testable(input_matrix);

    // assert
    compare_two_matrices(correct_vec, testable.eigenvectors);
    compare_two_matrices(correct_val, testable.eigenvalues);
}

TEST(EigendecompositionTests, Eigendecomposition2)
{
    // arrange
    Matrix<double> input_matrix{
        std::vector<std::vector<double>>{
            {52, 30, 49, 28},
            {30, 50, 8, 44},
            {49, 8, 46, 16},
            {28, 44, 16, 22}}};
    EigenDecomposer<double> testable;
    Matrix<double> correct_vec{
        std::vector<std::vector<double>>{
            {0.60945955, -0.29991942, -0.09987744, -0.72707077},
            {0.48785283, 0.65199675, 0.57724915, 0.06068999},
            {0.4665778, -0.60196233, 0.22156327, 0.60897966},
            {0.41576896, 0.35012847, -0.77956246, 0.31117293}}};
    Matrix<double> correct_val{
        std::vector<std::vector<double>>{
            {132.62787533, 0., 0., 0.},
            {0., 52.4423, 0., 0.},
            {0., 0., -11.54113078, 0.},
            {0., 0., 0., -3.52904455}}};

    // act
    testable(input_matrix);

    // assert
    compare_two_matrices(correct_vec, testable.eigenvectors);
    compare_two_matrices(correct_val, testable.eigenvalues);
}
