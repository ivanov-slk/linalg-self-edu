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
//             {-0.85714286, 0.39428571, 0.33142857},
//             {-0.42857143, -0.90285714, -0.03428571},
//             {0.28571429, -0.17142857, 0.94285714}}};
//     Matrix<double> correct_r{
//         std::vector<std::vector<double>>{
//             {-14.0, -21.0, 14.0},
//             {0.0, -175.0, 70.0},
//             {0.0, 0.0, -35.0}}};
//     compare_two_matrices<double>(correct_q, testable.matrix_q);
//     compare_two_matrices<double>(correct_r, testable.matrix_r);
// }

// TEST(QRDecompositionTests, QRDecompositionColumns)
// {
//     Matrix<double> input_matrix{
//         std::vector<std::vector<double>>{
//             {12., -51., 4., 6.},
//             {167., -68., -4., 24.},
//             {-41., 10., -24., 8.}}};
//     QRDecomposer<double> testable;
//     testable(input_matrix);
//     Matrix<double> correct_q{
//         std::vector<std::vector<double>>{
//             {-0.06961466, 0.9878042, -0.13927189},
//             {-0.96880397, -0.03365772, 0.24553211},
//             {0.23785008, 0.1520198, 0.95933171}}};
//     Matrix<double> correct_r{
//         std::vector<std::vector<double>>{
//             {-172.37749273, 71.80751851, -2.11164459, -21.7661827},
//             {0., -46.56909152, 0.43737254, 6.33519837},
//             {0., 0., -24.56317696, 12.73179297}}};
//     compare_two_matrices<double>(correct_q, testable.matrix_q);
//     compare_two_matrices<double>(correct_r, testable.matrix_r);
// }

// TESRDecompositionTests, QRDecompositionRows)
// {
//     // Matrix<double> input_matrix{
//     //     std::vector<std::vector<double>>{
//     //         {12.0, -51.0, 4.0},
//     //         {6.0, 167.0, -68.0},
//     //         {-4.0, 24.0, -41.0},
//     //         {10.0, -24.0, 8.0}}};
//     // Matrix<double> input_matrix{
//     //     std::vector<std::vector<double>>{
//     //         {10000.0, 10001.0},
//     //         {10001.0, 10002.0},
//     //         {10002.0, 10003.0},
//     //         {10003.0, 10004.0},
//     //         {10004.0, 10005.0}}};
//     // Matrix<double> input_matrix{
//     //     std::vector<std::vector<double>>{
//     //         {1., -1., 4.},
//     //         {1., 4., -2.},
//     //         {1., 4., 2.},
//     //         {1., -1., 0.}}};
//     Matrix<double> input_matrix{
//         std::vector<std::vector<double>>{
//             {-1., -1., 1.},
//             {1., 3., 3.},
//             {-1., -1., 5.},
//             {1., 3., 7.}}};
//     QRDecomposer<double> testable;
//     testable(input_matrix);
//     Matrix<double> correct_q{
//         std::vector<std::vector<double>>{
//             {-0.69748583, 0.29906048, -0.36166072, -0.54155135},
//             {-0.34874292, -0.93281644, 0.02962909, -0.08575542},
//             {0.23249528, -0.13904489, -0.93080449, 0.24538842},
//             {-0.58123819, 0.14519933, 0.04389362, 0.79947024}}};
//     Matrix<double> correct_r{
//         std::vector<std::vector<double>>{
//             {-17.20465053, -3.13868625, 6.74236305},
//             {0., -177.8542905, 71.4901946},
//             {0., 0., 35.05271198},
//             {0., 0., 0.}}};
//     testable.matrix_q.print_repr();
//     testable.matrix_r.print_repr();
//     testable.matrix_q.multiply(testable.matrix_r).print_repr();
//     compare_two_matrices<double>(input_matrix, testable.matrix_q.multiply(testable.matrix_r));
// }T(QRDecompositionTests, QRDecompositionRows)
// {
//     // Matrix<double> input_matrix{
//     //     std::vector<std::vector<double>>{
//     //         {12.0, -51.0, 4.0},
//     //         {6.0, 167.0, -68.0},
//     //         {-4.0, 24.0, -41.0},
//     //         {10.0, -24.0, 8.0}}};
//     // Matrix<double> input_matrix{
//     //     std::vector<std::vector<double>>{
//     //         {10000.0, 10001.0},
//     //         {10001.0, 10002.0},
//     //         {10002.0, 10003.0},
//     //         {10003.0, 10004.0},
//     //         {10004.0, 10005.0}}};
//     // Matrix<double> input_matrix{
//     //     std::vector<std::vector<double>>{
//     //         {1., -1., 4.},
//     //         {1., 4., -2.},
//     //         {1., 4., 2.},
//     //         {1., -1., 0.}}};
//     Matrix<double> input_matrix{
//         std::vector<std::vector<double>>{
//             {-1., -1., 1.},
//             {1., 3., 3.},
//             {-1., -1., 5.},
//             {1., 3., 7.}}};
//     QRDecomposer<double> testable;
//     testable(input_matrix);
//     Matrix<double> correct_q{
//         std::vector<std::vector<double>>{
//             {-0.69748583, 0.29906048, -0.36166072, -0.54155135},
//             {-0.34874292, -0.93281644, 0.02962909, -0.08575542},
//             {0.23249528, -0.13904489, -0.93080449, 0.24538842},
//             {-0.58123819, 0.14519933, 0.04389362, 0.79947024}}};
//     Matrix<double> correct_r{
//         std::vector<std::vector<double>>{
//             {-17.20465053, -3.13868625, 6.74236305},
//             {0., -177.8542905, 71.4901946},
//             {0., 0., 35.05271198},
//             {0., 0., 0.}}};
//     testable.matrix_q.print_repr();
//     testable.matrix_r.print_repr();
//     testable.matrix_q.multiply(testable.matrix_r).print_repr();
//     compare_two_matrices<double>(input_matrix, testable.matrix_q.multiply(testable.matrix_r));
// }
