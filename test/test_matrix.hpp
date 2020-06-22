#include <gtest/gtest.h>
#include "../src/matrix/matrix.cpp"
#include "../src/exceptions.hpp"
#include "../src/customconcepts.hpp"

// template <Number T>
void compare_two_matrices(const Matrix<float> &first, const Matrix<float> &second)
{
    std::vector<std::vector<float>> res_data = first.get_data();
    std::vector<std::vector<float>> cor_data = second.get_data();
    for (typename std::vector<float>::size_type i = 0; i < res_data.size(); ++i)
    {
        for (typename std::vector<float>::size_type j = 0; j < res_data[0].size(); ++j)
        {
            float a = res_data[i][j];
            float b = cor_data[i][j];
            ASSERT_FLOAT_EQ(a, b);
        }
    }
}

TEST(MatrixTests, Empty)
{
    std::vector<std::vector<int>> data;
    Matrix<int> testable{data};
    ASSERT_TRUE(testable.empty());
}

TEST(MatrixTests, NotEmpty)
{
    std::vector<std::vector<int>> data{
        {1, 2, 3},
        {4, 5, 6}};
    Matrix<int> testable{data};
    ASSERT_TRUE(!testable.empty());
}

TEST(MatrixTests, CorrectShape)
{
    std::vector<std::vector<int>> data{
        {1, 2, 3},
        {4, 5, 6}};
    Matrix<int> testable{data};
    ASSERT_EQ(std::make_pair(2, 3), testable.get_shape());
}

TEST(MatrixTests, CorrectShapeEmpty)
{
    std::vector<std::vector<int>> data;
    Matrix<int> testable{data};
    ASSERT_EQ(std::make_pair(0, 0), testable.get_shape());
}

TEST(MatrixTests, ThrowsBadShape)
{
    std::vector<std::vector<int>> data{
        {1, 2, 3},
        {4, 5}};
    ASSERT_THROW((Matrix<int>{data}), BadDimensionsException);
}

TEST(MatrixTests, Equal)
{
    std::vector<std::vector<int>> data1{
        {1, 2, 3},
        {4, 5, 6}};
    std::vector<std::vector<int>> data2{
        {1, 2, 3},
        {4, 5, 6}};
    Matrix<int> testable1{data1};
    Matrix<int> testable2{data2};
    ASSERT_TRUE(testable1.equals(testable2));
}

TEST(MatrixTests, NotEqual)
{
    std::vector<std::vector<int>> data1{
        {1, 2, 3},
        {4, 5, 6}};
    std::vector<std::vector<int>> data2{
        {1, 5, 3},
        {4, 2, 6}};
    Matrix<int> testable1{data1};
    Matrix<int> testable2{data2};
    ASSERT_FALSE(testable1.equals(testable2));
}

TEST(MatrixTests, AddReturnsCorrect)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2{
        std::vector<std::vector<float>>{
            {1., 1., 1.},
            {2., 2., 2.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {2., 3., 4.},
            {6., 7., 8.}}};
    ASSERT_EQ(mat1.add(mat2), correct);
}

TEST(MatrixTests, AddReturnsSame)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2;
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_EQ(mat1.add(mat2), correct);
}

// TEST(MatrixTests, AddThrowsDimensionMismatch)
// {
//     Matrix<float> mat1{
//         std::vector<std::vector<float>>{
//             {1., 2., 3.},
//             {4., 5., 6.}}};
//     Matrix<float> mat2{
//         std::vector<std::vector<float>>{
//             {1., 1., 1.},
//             {2., 2.}}};
//     ASSERT_THROW(mat1.add(mat2), BadDimensionsException);
//     // currently impossible, because it will throw on construction of the second matrix
//     // keeping this test for reference though
// }

TEST(MatrixTests, SubtractReturnsCorrect)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2{
        std::vector<std::vector<float>>{
            {1., 1., 1.},
            {2., 2., 2.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {0., 1., 2.},
            {2., 3., 4.}}};
    ASSERT_EQ(mat1.subtract(mat2), correct);
}

TEST(MatrixTests, SubtractReturnsSame)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2;
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_EQ(mat1.subtract(mat2), correct);
}

TEST(MatrixTests, ElementMultiplyReturnsCorrect)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2{
        std::vector<std::vector<float>>{
            {1., 1., 1.},
            {2., 2., 2.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {8., 10., 12.}}};
    ASSERT_EQ(mat1.el_multiply(mat2), correct);
}

TEST(MatrixTests, ElementMultiplyReturnsSame)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2;
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_EQ(mat1.el_multiply(mat2), correct);
}

TEST(MatrixTests, DivideReturnsCorrect)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2{
        std::vector<std::vector<float>>{
            {1., 1., 1.},
            {2., 2., 2.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {2., 2.5, 3.}}};
    ASSERT_EQ(mat1.el_divide(mat2), correct);
}

TEST(MatrixTests, DivideReturnsSame)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2;
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_EQ(mat1.el_divide(mat2), correct);
}

TEST(MatrixTests, Transpose)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 4.},
            {2., 5.},
            {3., 6.}}};
    ASSERT_EQ(testable.transpose(), correct);
}

TEST(MatrixTests, TransposeTranspose)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    ASSERT_EQ(testable.transpose().transpose(), testable);
}

TEST(MatrixTests, TransposeSquare)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.},
            {7., 8., 9.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {1., 4., 7.},
            {2., 5., 8.},
            {3., 6., 9.}}};
    ASSERT_EQ(testable.transpose(), correct);
}

TEST(MatrixTests, MatrixMultiply1)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
            {4., 5., 6.}}};
    Matrix<float> mat2{
        std::vector<std::vector<float>>{
            {1., 1.},
            {2., 2.},
            {3., 3.}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {14., 14.},
            {32., 32.}}};
    ASSERT_EQ(mat1.multiply(mat2), correct);
}

TEST(MatrixTests, MatrixMultiply2)
{
    // arrange
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {51.5, 72.2},
            {48.0, 52.9},
            {8.4, 23.7}}};
    Matrix<float> mat2{
        std::vector<std::vector<float>>{
            {87.7, 12.48, 6.123},
            {12.12, 54.48, 21.789}}};
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {5391.614, 4576.176, 1888.5003},
            {4850.748, 3481.032, 1446.5421},
            {1023.924, 1396.008, 567.8325}}};

    // act
    Matrix<float> result = mat1.multiply(mat2);

    // assert
    compare_two_matrices(result, correct);
}

TEST(MatrixTests, MatrixMultiplyEmpty)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {51.5, 72.2},
            {48.0, 52.9},
            {8.4, 23.7}}};
    Matrix<float> mat2;
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {51.5, 72.2},
            {48.0, 52.9},
            {8.4, 23.7}}};
    ASSERT_EQ(mat1.multiply(mat2), correct);
}

TEST(MatrixTests, MatrixMultiplyThrows)
{
    Matrix<float> mat1{
        std::vector<std::vector<float>>{
            {51.5, 72.2},
            {48.0, 52.9},
            {8.4, 23.7}}};
    Matrix<float> mat2{
        std::vector<std::vector<float>>{
            {1., 2.},
            {3., 4.},
            {5., 6.}}};
    ASSERT_THROW(mat1.multiply(mat2), BadDimensionsException);
}

TEST(MatrixTests, MatrixMultiplyTranspose)
{
    Matrix<float> a{std::vector<std::vector<float>>{
        {1.2, 3.4, -5.7},
        {-5.3, 8.7, 4.127}}};
    Matrix<float> b{std::vector<std::vector<float>>{
        {34.5, 234.34},
        {876.43, -5.1243},
        {-675.234, 54.2}}};
    Matrix<float> abt = a.multiply(b).transpose();
    Matrix<float> atbt = b.transpose().multiply(a.transpose());
    compare_two_matrices(abt, atbt);
}

// test norm (frobenius, vector, different p-s)
TEST(MatrixTests, NormsMatrix)
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

TEST(MatrixTests, NormsVectors)
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
TEST(MatrixTests, Trace)
{
    Matrix<float> a{std::vector<std::vector<float>>{
        {1.2, 3.4, -5.7},
        {-5.3, 8.7, 4.127},
        {-3.23, 34.4, 23.6}}};
    ASSERT_FLOAT_EQ(a.trace(), 33.5);
}

TEST(MatrixTests, TraceNonsquare)
{
    Matrix<float> a{std::vector<std::vector<float>>{
        {1.2, 3.4, -5.7},
        {-5.3, 8.7, 4.127}}};
    ASSERT_FLOAT_EQ(a.trace(), 0.0);
}

// test is_symmetric (A = A^T)

// test frobenius norm = sqroot(trace(A*A^T))