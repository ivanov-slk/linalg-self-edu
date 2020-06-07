#include <gtest/gtest.h>
#include "../src/matrix/matrix.cpp"
#include "../src/matrix/denserepresentation.hpp"

TEST(MatrixTests, Empty)
{
    std::vector<std::vector<int>> data;
    Matrix<int, DenseRepresentation> testable{data};
    ASSERT_TRUE(testable.empty());
}

TEST(MatrixTests, NotEmpty)
{
    std::vector<std::vector<int>> data{
        {1, 2, 3},
        {4, 5, 6}};
    Matrix<int, DenseRepresentation> testable{data};
    ASSERT_TRUE(!testable.empty());
}

// TEST(MatrixTests, CorrectShape)
// {
//     std::vector<std::vector<int>> data{
//         {1, 2, 3},
//         {4, 5, 6}};
//     std::unique_ptr<IMatrix<int>> testable = MakeDenseMatrix<int>(data);
//     ASSERT_EQ(std::make_pair(2, 3), testable->get_shape());
// }

// TEST(MatrixTests, CorrectShapeEmpty)
// {
//     std::vector<std::vector<int>> data;
//     std::unique_ptr<IMatrix<int>> testable = MakeDenseMatrix<int>(data);
//     ASSERT_EQ(std::make_pair(0, 0), testable->get_shape());
// }

// TEST(MatrixTests, ThrowsBadShape)
// {
//     std::vector<std::vector<int>> data{
//         {1, 2, 3},
//         {4, 5}};
//     ASSERT_THROW(std::unique_ptr<IMatrix<int>> testable = MakeDenseMatrix<int>(data);,
//                                                                                      BadDimensionsException);
// }

// TEST(MatrixTests, AddReturnsCorrect)
// {
//     Matrix<float> mat1{
//         std::vector<std::vector<float>>{
//             {1., 2., 3.},
//             {4., 5., 6.}}};
//     Matrix<float> mat2{
//         std::vector<std::vector<float>>{
//             {1., 1., 1.},
//             {2., 2., 2.}}};
//     Matrix<float> correct{
//         std::vector<std::vector<float>>{
//             {2., 3., 4.},
//             {6., 7., 8.}}};
//     ASSERT_EQ(mat1.add(mat2), correct);
// }

// TEST(MatrixTests, AddReturnsSame)
// {
//     Matrix<float> mat1{
//         std::vector<std::vector<float>>{
//             {1., 2., 3.},
//             {4., 5., 6.}}};
//     Matrix<float> mat2;
//     Matrix<float> correct{
//         std::vector<std::vector<float>>{
//             {1., 2., 3.},
//             {4., 5., 6.}}};
//     ASSERT_EQ(mat1.add(mat2), correct);
// }

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
// }