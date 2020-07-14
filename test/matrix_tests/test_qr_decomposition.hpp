#pragma once
#include "matrix_tests_utilities.hpp"

TEST(QRDecompositionTests, QRDecompositionSquare)
{
    Matrix<double> input_matrix{
        std::vector<std::vector<double>>{
            {12.0, -51.0, 4.0},
            {6.0, 167.0, -68.0},
            {-4.0, 24.0, -41.0}}};
    QRDecomposer<double> testable;
    testable(input_matrix);
    Matrix<double> correct_q{
        std::vector<std::vector<double>>{
            {-0.85714286, 0.39428571, 0.33142857},
            {-0.42857143, -0.90285714, -0.03428571},
            {0.28571429, -0.17142857, 0.94285714}}};
    Matrix<double> correct_r{
        std::vector<std::vector<double>>{
            {-14.0, -21.0, 14.0},
            {0.0, -175.0, 70.0},
            {0.0, 0.0, -35.0}}};
    compare_two_matrices<double>(correct_q, testable.matrix_q);
    compare_two_matrices<double>(correct_r, testable.matrix_r);
}

// TEST(QRDecompositionTests, QRDecompositionRows)
// {
//     Matrix<double> input_matrix;
//     QRDecomposer<double> testable;
//     testable(input_matrix);
//     Matrix<double> correct_q;
//     Matrix<double> correct_r;
//     compare_two_matrices(correct_q, testable.matrix_q);
//     compare_two_matrices(correct_r, testable.matrix_r);
// }

// TEST(QRDecompositionTests, QRDecompositionColumns)
// {
//     Matrix<double> input_matrix;
//     QRDecomposer<double> testable;
//     testable(input_matrix);
//     Matrix<double> correct_q;
//     Matrix<double> correct_r;
//     compare_two_matrices(correct_q, testable.matrix_q);
//     compare_two_matrices(correct_r, testable.matrix_r);
// }
