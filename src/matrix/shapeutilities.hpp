#pragma once
#include <vector>

#include "../customconcepts.hpp"

/**
 * @brief Extracts a row from a matrix's raw data.
 */
template <Number T>
class ExtractRowRaw
{
public:
    std::vector<T> operator()(const std::vector<std::vector<T>> &data, int row)
    {
    }
};

/**
 * @brief Extracts a column from a matrix's raw data.
 */
template <Number T>
class ExtractColumnRaw
{
public:
    std::vector<std::vector<T>> operator()(const std::vector<std::vector<T>> &data, int col) {}
};

/**
 * @brief Extracts an adjoint matrix raw data from a matrix's raw data.
 */
template <Number T>
class ExtractAdjointRaw
{
public:
    std::vector<std::vector<T>> operator()(const std::vector<std::vector<T>> &data, int row, int col) {}
};

/**
 * @brief Extracts a submatrix as raw data from a matrix and a given top-left element.
 */
template <Number T>
class ExtractSubmatrixRaw
{
    std::vector<std::vector<T>> operator()(const std::vector<std::vector<T>> &data, int row, int col) {}
};