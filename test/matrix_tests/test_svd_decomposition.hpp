#pragma once
#include "matrix_tests_utilities.hpp"

TEST(SVDDecompositionTests, SVDDecompositionSquare) {
    Matrix<double> input_matrix{std::vector<std::vector<double>>{
        {4., 1., 3.}, {8., 7., -2.}, {1., 5., 4.}}};
    SVDDecomposer<double> testable;
    SVDDecomposition<double> output = testable(input_matrix);
    ASSERT_TRUE(output.matrix_s.is_diagonal());
    Matrix<double> result =
        output.matrix_u.multiply(output.matrix_s).multiply(output.matrix_v);
    compare_two_matrices(input_matrix, result);
    ASSERT_FLOAT_EQ(result.sum(-1, 1).extract_element(0, 0),
                    input_matrix.sum(-1, 1).extract_element(0, 0));
}

TEST(SVDDecompositionTests, SVDDecompositionRows) {
    Matrix<double> input_matrix{std::vector<std::vector<double>>{
        {12., -51., 4.}, {6., 167., -68.}, {-4., 24., -41.}, {10., -24., 8.}}};
    SVDDecomposer<double> testable;
    SVDDecomposition<double> output = testable(input_matrix);
    ASSERT_TRUE(output.matrix_s.is_diagonal());
    Matrix<double> result =
        output.matrix_u.multiply(output.matrix_s).multiply(output.matrix_v);
    compare_two_matrices(input_matrix, result);
    ASSERT_FLOAT_EQ(result.sum(-1, 1).extract_element(0, 0),
                    input_matrix.sum(-1, 1).extract_element(0, 0));
}

TEST(SVDDecompositionTests, SVDDecompositionColumns) {
    Matrix<double> input_matrix{std::vector<std::vector<double>>{
        {12., -51., 4., 6.}, {167., -68., -4., 24.}, {-41., 10., -24., 8.}}};
    SVDDecomposer<double> testable;
    SVDDecomposition<double> output = testable(input_matrix);
    ASSERT_TRUE(output.matrix_s.is_diagonal());
    Matrix<double> result =
        output.matrix_u.multiply(output.matrix_s).multiply(output.matrix_v);
    compare_two_matrices(input_matrix, result);
    ASSERT_FLOAT_EQ(result.sum(-1, 1).extract_element(0, 0),
                    input_matrix.sum(-1, 1).extract_element(0, 0));
}
