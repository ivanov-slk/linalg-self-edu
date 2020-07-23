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