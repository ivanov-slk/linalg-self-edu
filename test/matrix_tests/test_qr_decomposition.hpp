#pragma once
#include "matrix_tests_utilities.hpp"

// TEST(QRDecompositionTests, QRDecompositionSquare)
// {
//     Matrix<float> input_matrix{
//         std::vector<std::vector<float>>{
//             {1.0, 2.0, 1.5},
//             {-2.3, -7.54, 2.4},
//             {-1.0, 3.4, 2.9}}};
//     QRDecomposer<float> testable;
//     testable(input_matrix);
//     Matrix<float> correct_q;
//     Matrix<float> correct_r;
//     testable.matrix_q.print_repr();
//     testable.matrix_r.print_repr();
//     compare_two_matrices(correct_q, testable.matrix_q);
//     compare_two_matrices(correct_r, testable.matrix_r);
// }

// TEST(QRDecompositionTests, QRDecompositionRows)
// {
//     Matrix<float> input_matrix;
//     QRDecomposer<float> testable;
//     testable(input_matrix);
//     Matrix<float> correct_q;
//     Matrix<float> correct_r;
//     compare_two_matrices(correct_q, testable.matrix_q);
//     compare_two_matrices(correct_r, testable.matrix_r);
// }

// TEST(QRDecompositionTests, QRDecompositionColumns)
// {
//     Matrix<float> input_matrix;
//     QRDecomposer<float> testable;
//     testable(input_matrix);
//     Matrix<float> correct_q;
//     Matrix<float> correct_r;
//     compare_two_matrices(correct_q, testable.matrix_q);
//     compare_two_matrices(correct_r, testable.matrix_r);
// }
