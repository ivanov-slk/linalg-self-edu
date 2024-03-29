#include "matrix_tests_utilities.hpp"

// test norm (frobenius, vector, different p-s)
TEST(MatrixPropertiesTests, NormsMatrix)
{
    Matrix<float> a{std::vector<std::vector<float>>{
        {1.2, 3.4, -5.7},
        {-5.3, 8.7, 4.127}}};
    Matrix<float> b{std::vector<std::vector<float>>{
        {34.5, 234.34},
        {876.43, -5.1243},
        {-675.234, 54.2}}};
    float norm_a_1 = a.norm(1);
    float norm_a_2 = a.norm(2);
    float norm_b_1 = b.norm(1);
    float norm_b_2 = b.norm(2);
    ASSERT_FLOAT_EQ(norm_a_1, 28.427);
    ASSERT_FLOAT_EQ(norm_a_2, 12.895818);
    ASSERT_FLOAT_EQ(norm_b_1, 1879.8284);
    ASSERT_FLOAT_EQ(norm_b_2, 1132.7577);
}

TEST(MatrixPropertiesTests, NormsVectors)
{
    Matrix<float> a{
        std::vector<std::vector<float>>{
            {1.2, 3.4, -5.7, -5.3, 8.7, 4.127}}};
    Matrix<float> b{std::vector<std::vector<float>>{
        {34.5},
        {234.34},
        {876.43},
        {-5.1243},
        {-675.234},
        {54.2}}};
    float norm_a_1 = a.norm(1);
    float norm_a_2 = a.norm(2);
    float norm_b_1 = b.norm(1);
    float norm_b_2 = b.norm(2);
    ASSERT_FLOAT_EQ(norm_a_1, 28.427);
    ASSERT_FLOAT_EQ(norm_a_2, 12.895818);
    ASSERT_FLOAT_EQ(norm_b_1, 1879.8284);
    ASSERT_FLOAT_EQ(norm_b_2, 1132.7577);
}

// test trace
TEST(MatrixPropertiesTests, Trace)
{
    Matrix<float> a{std::vector<std::vector<float>>{
        {1.2, 3.4, -5.7},
        {-5.3, 8.7, 4.127},
        {-3.23, 34.4, 23.6}}};
    ASSERT_FLOAT_EQ(a.trace(), 33.5);
}

TEST(MatrixPropertiesTests, TraceNonsquare)
{
    Matrix<float> a{std::vector<std::vector<float>>{
        {1.2, 3.4, -5.7},
        {-5.3, 8.7, 4.127}}};
    ASSERT_FLOAT_EQ(a.trace(), 0.0);
}

// test is_symmetric (A = A^T)
TEST(MatrixPropertiesTests, Symmetric)
{
    Matrix<int> testable{std::vector<std::vector<int>>{
        {1, 2, 3},
        {2, 1, 2},
        {3, 2, 1}}};
    ASSERT_TRUE(testable.is_symmetric());
}

TEST(MatrixPropertiesTests, NotSymmetric)
{
    Matrix<int> testable{std::vector<std::vector<int>>{
        {1, 2, 3},
        {55, 1, 2},
        {3, 2, 1}}};
    ASSERT_FALSE(testable.is_symmetric());
}

// test is_diagonal
TEST(MatrixPropertiesTests, Diagonal)
{
    Matrix<double> testable{std::vector<std::vector<double>>{
        {1., 0., 0.},
        {0., 1., 0.},
        {0., 0., 1.}}};
    ASSERT_TRUE(testable.is_diagonal());
}

TEST(MatrixPropertiesTests, Diagonal1)
{
    Matrix<double> testable{std::vector<std::vector<double>>{
        {1., 0.},
        {0., 1.},
        {0., 0.}}};
    ASSERT_TRUE(testable.is_diagonal());
}

TEST(MatrixPropertiesTests, Diagonal2)
{
    Matrix<double> testable{std::vector<std::vector<double>>{
        {1., 0., 0.},
        {0., 1., 0.}}};
    ASSERT_TRUE(testable.is_diagonal());
}

TEST(MatrixPropertiesTests, NotDiagonal)
{
    Matrix<double> testable{std::vector<std::vector<double>>{
        {1., 0., 0.},
        {0., 1., 2.},
        {0., 0., 1.}}};
    ASSERT_FALSE(testable.is_diagonal());
}

TEST(MatrixPropertiesTests, NotDiagonal1)
{
    Matrix<double> testable{std::vector<std::vector<double>>{
        {1., 0.},
        {0., 1.},
        {0., 2.}}};
    ASSERT_FALSE(testable.is_diagonal());
}

TEST(MatrixPropertiesTests, NotDiagonal2)
{
    Matrix<double> testable{std::vector<std::vector<double>>{
        {1., 0., 0.},
        {0., 1., 2.}}};
    ASSERT_FALSE(testable.is_diagonal());
}

// test frobenius norm = sqroot(trace(A*A^T))
TEST(MatrixPropertiesTests, FrobeniusEqualsTrace)
{
    Matrix<float> testable{std::vector<std::vector<float>>{
        {34.5, 234.34},
        {876.43, -5.1243},
        {-675.234, 54.2}}};
    float frobenius_norm = testable.norm(2);
    float trace_frobenius = std::sqrt(testable.multiply(
                                                  testable.transpose())
                                          .trace());
    ASSERT_FLOAT_EQ(frobenius_norm, trace_frobenius);
}