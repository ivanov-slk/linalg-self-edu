#pragma once
#include "matrix_tests_utilities.hpp"
// σ1=11.97, σ2=5.57, σ3=3.25,
TEST(SVDDecompositionTests, SVDDecomposition1)
{
    Matrix<double> input_matrix{
        std::vector<std::vector<double>>{
            {4., 1., 3.},
            { 8., 7., -2. },
        { 1., 5., 4. }} };
    SVDDecomposer<double> testable;
    testable(input_matrix);
    Matrix<double> result = testable.matrix_u.transpose().multiply(testable.matrix_s)
        .multiply(testable.matrix_v.transpose());
    result.print_repr();
    compare_two_matrices(input_matrix, result);
    ASSERT_FLOAT_EQ(result.sum(-1, 1).extract_element(0, 0),
        input_matrix.sum(-1, 1).extract_element(0, 0));
}