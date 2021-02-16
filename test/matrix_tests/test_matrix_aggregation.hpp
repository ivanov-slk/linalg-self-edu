#pragma once
#include "matrix_tests_utilities.hpp"

TEST(MatrixAggregationTests, SumEmpty)
{
    Matrix<float> testable;
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {0.}} };
    ASSERT_EQ(testable.sum(-1, 1), correct);
}

TEST(MatrixAggregationTests, SumAll)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1.5, 2., 3.},
        { 4., 5., 6. }} };
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {21.5}} };
    ASSERT_EQ(testable.sum(-1, 1), correct);
}

TEST(MatrixAggregationTests, SumRows)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
        { 4., 5., 6. }} };
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {6.},
        { 15. }} };
    ASSERT_EQ(testable.sum(0, 1), correct);
}

TEST(MatrixAggregationTests, SumColumns)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
        { 4., 5., 6. }} };
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {5., 7., 9.}} };
    ASSERT_EQ(testable.sum(1, 1), correct);
}

TEST(MatrixAggregationTests, SumAllPower)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1.5, 2., 3.},
        { 4., 5., 6. }} };
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {92.25}} };
    ASSERT_EQ(testable.sum(-1, 2), correct);
}

TEST(MatrixAggregationTests, SumRowsPower)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
        { 4., 5., 6. }} };
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {14.},
        { 77. }} };
    ASSERT_EQ(testable.sum(0, 2), correct);
}

TEST(MatrixAggregationTests, SumColumnsPower)
{
    Matrix<float> testable{
        std::vector<std::vector<float>>{
            {1., 2., 3.},
        { 4., 5., 6. }} };
    Matrix<float> correct{
        std::vector<std::vector<float>>{
            {65., 133., 243.}} };
    ASSERT_EQ(testable.sum(1, 3), correct);
}