#pragma once
#include "matrix_tests_utilities.hpp"

// TEST(QRDecompositionTests, QRDecompositionSquare)
// {
//     Matrix<double> input_matrix{
//         std::vector<std::vector<double>>{
//             {12.0, -51.0, 4.0},
//             {6.0, 167.0, -68.0},
//             {-4.0, 24.0, -41.0}}};
//     QRDecomposer<double> testable;
//     testable(input_matrix);
//     Matrix<double> correct_q{
//         std::vector<std::vector<double>>{
//             {0.85714285714, -0.39428571428, 0.33142857142},
//             {0.42857142857, 0.90285714285, -0.03428571428},
//             {-0.28571428571, 0.17142857142, 0.94285714285}}};
//     Matrix<double> correct_r{
//         std::vector<std::vector<double>>{
//             {14.0, 21.0, -14.0},
//             {0.0, 175.0, -70.0},
//             {0.0, 0.0, -35.0}}};
//     compare_two_matrices<double>(correct_q, testable.matrix_q);
//     compare_two_matrices<double>(correct_r, testable.matrix_r);
// }

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
