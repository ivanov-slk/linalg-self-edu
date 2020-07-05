#include "matrix_tests_utilities.hpp"

TEST(MatrixShapeUtilitiesTests, ExtractRow1)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 2., 3.}}};
    ASSERT_EQ(testable.extract_row(0), correct);
}

TEST(MatrixShapeUtilitiesTests, ExtractRow2)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {4., 5., 6.}}};
    ASSERT_EQ(testable.extract_row(1), correct);
}

TEST(MatrixShapeUtilitiesTests, ExtractRowThrows)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_THROW(testable.extract_row(2), BadDimensionsException);
}

TEST(MatrixShapeUtilitiesTests, ExtractColumn1)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1.},
            {4.}}};
    ASSERT_EQ(testable.extract_column(0), correct);
}

TEST(MatrixShapeUtilitiesTests, ExtractColumn2)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {2.},
            {5.}}};
    ASSERT_EQ(testable.extract_column(1), correct);
}

TEST(MatrixShapeUtilitiesTests, ExtractColumnThrows)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_THROW(testable.extract_column(3), BadDimensionsException);
}

TEST(MatrixShapeUtilitiesTests, ExtractWithout1)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {2., 3.},
            {5., 6.}}};
    ASSERT_EQ(testable.extract_without(-1, 0), correct);
}

TEST(MatrixShapeUtilitiesTests, ExtractWithout2)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 2., 3.}}};
    ASSERT_EQ(testable.extract_without(1, -1), correct);
}

TEST(MatrixShapeUtilitiesTests, ExtractWithout3)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.},
            {7., 8., 9.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {5., 6.},
            {8., 9.}}};
    ASSERT_EQ(testable.extract_without(0, 0), correct);
}

TEST(MatrixShapeUtilitiesTests, ExtractWithout4)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.},
            {7., 8., 9.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 3.},
            {7., 9.}}};
    ASSERT_EQ(testable.extract_without(1, 1), correct);
}

TEST(MatrixShapeUtilitiesTests, ExtractWithoutThrows1)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_THROW(testable.extract_without(-1, 3), BadDimensionsException);
}

TEST(MatrixShapeUtilitiesTests, ExtractWithoutThrows2)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_THROW(testable.extract_without(3, -3), BadDimensionsException);
}

TEST(MatrixShapeUtilitiesTests, ExtractSubmatrix1)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.},
            {7., 8., 9.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {5., 6.},
            {8., 9.}}};
    ASSERT_EQ(testable.extract_submatrix(1, 1), correct);
}

TEST(MatrixShapeUtilitiesTests, ExtractSubmatrix2)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.},
            {7., 8., 9.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.},
            {7., 8., 9.}}};
    ASSERT_EQ(testable.extract_submatrix(0, 0), correct);
}

TEST(MatrixShapeUtilitiesTests, ExtractSubmatrix3)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.},
            {7., 8., 9.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {9.}}};
    ASSERT_EQ(testable.extract_submatrix(2, 2), correct);
}

TEST(MatrixShapeUtilitiesTests, ExtractSubmatrix4)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {2., 3.},
            {5., 6.}}};
    ASSERT_EQ(testable.extract_submatrix(0, 1), correct);
}

TEST(MatrixShapeUtilitiesTests, ExtractSubmatrix5)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {4., 5., 6.}}};
    ASSERT_EQ(testable.extract_submatrix(1, 0), correct);
}

TEST(MatrixShapeUtilitiesTests, ExtractSubmatrixThrows1)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_THROW(testable.extract_submatrix(-1, 3), BadDimensionsException);
}

TEST(MatrixShapeUtilitiesTests, ExtractSubmatrixThrows2)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_THROW(testable.extract_submatrix(1, 3), BadDimensionsException);
}