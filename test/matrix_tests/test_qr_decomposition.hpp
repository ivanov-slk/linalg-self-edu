#pragma once
#include "matrix_tests_utilities.hpp"

TEST(QRDecompositionTests, QRDecompositionSquare1) {
    Matrix<double> input_matrix{std::vector<std::vector<double>>{
        {12.0, -51.0, 4.0}, {6.0, 167.0, -68.0}, {-4.0, 24.0, -41.0}}};
    QRDecomposer<double> testable;
    QRDecomposition<double> output = testable(input_matrix);
    Matrix<double> correct_q{std::vector<std::vector<double>>{
        {-0.85714286, 0.39428571, 0.33142857},
        {-0.42857143, -0.90285714, -0.03428571},
        {0.28571429, -0.17142857, 0.94285714}}};
    Matrix<double> correct_r{std::vector<std::vector<double>>{
        {-14.0, -21.0, 14.0}, {0.0, -175.0, 70.0}, {0.0, 0.0, -35.0}}};
    compare_two_matrices<double>(correct_q, output.matrix_q);
    compare_two_matrices<double>(correct_r, output.matrix_r);
}

TEST(QRDecompositionTests, QRDecompositionSquare2) {
    Matrix<double> input_matrix{std::vector<std::vector<double>>{
        {0.70000, 0.70711}, {0.70001, 0.70711}}};
    QRDecomposer<double> testable;
    QRDecomposition<double> output = testable(input_matrix);
    compare_two_matrices<double>(input_matrix,
                                 output.matrix_q.multiply(output.matrix_r));
}

TEST(QRDecompositionTests, QRDecompositionSquare3) {
    Matrix<double> input_matrix{
        std::vector<std::vector<double>>{{6., 6., -77., 59.},
                                         {-13., 20., -81., 1.},
                                         {-33., -35, -65., -74.},
                                         {98., 92., 42., 2.}}};
    QRDecomposer<double> testable;
    QRDecomposition<double> output = testable(input_matrix);
    Matrix<double> correct_q{std::vector<std::vector<double>>{
        {-0.05747485, -0.01618887, -0.81502153, -0.57634579},
        {0.12452884, -0.98526564, -0.06030549, 0.10053572},
        {0.31611168, 0.15087768, -0.55752515, 0.75264536},
        {-0.93875589, -0.0789016, -0.14583849, 0.30206465}}};
    Matrix<double> correct_r{std::vector<std::vector<double>>{
        {-104.39348639, -95.28372262, -65.63627902, -28.53626316},
        {-0., -32.34211193, 67.93214396, -13.26316034},
        {0., -0., 97.75532054, -7.18139135},
        {0., 0., 0., -88.9954936}}};

    ////////////////////////////   keep for reference in future testing
    /////////////////////////
    // // sum stuff
    // std::vector<std::vector<double>> data = input_matrix.get_data();
    // double temp_sum = 0.;
    // for (auto &row : data)
    // {
    //     for (auto &el : row)
    //     {
    //         temp_sum += el;
    //     }
    // }
    // data = testable.matrix_q.multiply(testable.matrix_r).get_data();
    // long double result_sum = 0.;
    // for (auto &row : data)
    // {
    //     for (auto &el : row)
    //     {
    //         result_sum += el;
    //     }
    // }
    // std::cout << result_sum << "    =======    " << temp_sum << '\n';
    // ASSERT_DOUBLE_EQ(temp_sum, result_sum);
    ////////////////////////////   and consider implementing it
    /////////////////////////
    compare_two_matrices<double>(correct_q, output.matrix_q);
    compare_two_matrices<double>(correct_r, output.matrix_r);
}

TEST(QRDecompositionTests, QRDecompositionColumns) {
    Matrix<double> input_matrix{std::vector<std::vector<double>>{
        {12., -51., 4., 6.}, {167., -68., -4., 24.}, {-41., 10., -24., 8.}}};
    QRDecomposer<double> testable;
    QRDecomposition<double> output = testable(input_matrix);
    Matrix<double> correct_q{
        std::vector<std::vector<double>>{{-0.06961466, 0.9878042, -0.13927189},
                                         {-0.96880397, -0.03365772, 0.24553211},
                                         {0.23785008, 0.1520198, 0.95933171}}};
    Matrix<double> correct_r{std::vector<std::vector<double>>{
        {-172.37749273, 71.80751851, -2.11164459, -21.7661827},
        {0., -46.56909152, 0.43737254, 6.33519837},
        {0., 0., -24.56317696, 12.73179297}}};
    compare_two_matrices<double>(correct_q, output.matrix_q);
    compare_two_matrices<double>(correct_r, output.matrix_r);
}

TEST(QRDecompositionTests, QRDecompositionRows) {
    Matrix<long double> input_matrix{std::vector<std::vector<long double>>{
        {12., -51., 4.}, {6., 167., -68.}, {-4., 24., -41.}, {10., -24., 8.}}};
    QRDecomposer<long double> testable;
    QRDecomposition<long double> output = testable(input_matrix);
    Matrix<long double> correct_q{std::vector<std::vector<long double>>{
        {-0.69748583, 0.29906048, -0.36166072, -0.54155135},
        {-0.34874292, -0.93281644, 0.02962909, -0.08575542},
        {0.23249528, -0.13904489, -0.93080449, 0.24538842},
        {-0.58123819, 0.14519933, 0.04389362, 0.79947024}}};
    Matrix<long double> correct_r{std::vector<std::vector<long double>>{
        {-17.20465053, -3.13868625, 6.74236305},
        {0., -177.8542905, 71.4901946},
        {0., 0., 35.05271198},
        {0., 0., 0.}}};
    compare_two_matrices<long double>(
        input_matrix, output.matrix_q.multiply(output.matrix_r));
}