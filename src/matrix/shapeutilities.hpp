#pragma once
#include <vector>

#include "../customconcepts.hpp"

/**
 * @brief Extracts an element from a matrix's raw data.
 */
template <Number T>
class ExtractElementRaw
{
public:
    T operator()(const std::vector<std::vector<T>> &data, int row, int col)
    {
        T element = data.at(row).at(col);
        return element;
    }
};

/**
 * @brief Extracts a row from a matrix's raw data.
 */
template <Number T>
class ExtractRowRaw
{
public:
    std::vector<std::vector<T>> operator()(const std::vector<std::vector<T>> &data, int row)
    {
        std::vector<std::vector<T>> out{std::vector<T>{data.at(row)}};
        return out;
    }
};

/**
 * @brief Extracts a column from a matrix's raw data.
 */
template <Number T>
class ExtractColumnRaw
{
public:
    std::vector<std::vector<T>> operator()(const std::vector<std::vector<T>> &data, int col)
    {
        std::vector<std::vector<T>> out;
        for (const auto &row : data)
        {
            out.push_back(std::vector<T>{row.at(col)});
        }
        return out;
    }
};

/**
 * @brief Extracts a matrix raw data without the given row and/or column from a matrix's raw data.
 * @param int row: The row anchor. Starts at zero.
 * @param int col: The column anchor. Starts at zero.
 * @param std::function<T(T, T)> A boolean function that compares two elements of type T. If std::not_equal, then
 * extracts a matrix raw data without the given row and/or column from a matrix's raw data.
 * If std::greater_equal, then extracts a submatrix from the given raw data with (row, col) being
 * the top left element.
 * @return A raw matrix representation without the given row/column.
 */
template <Number T>
class ExtractSubmatrixRaw
{
public:
    std::vector<std::vector<T>> operator()(const std::vector<std::vector<T>> &data,
                                           int row,
                                           int col,
                                           std::function<T(T, T)> comparison_op)
    {
        std::vector<std::vector<T>> out;
        out.reserve(data.size());
        int row_count = 0; // clumsy
        for (auto &row_el : data)
        {
            if (comparison_op(row_count, row))
            {
                std::vector<T> temp_row;
                int col_count = 0; // clumsy
                for (auto &col_el : row_el)
                {
                    if (comparison_op(col_count, col))
                    {
                        temp_row.push_back(col_el);
                    }
                    col_count++;
                }
                out.push_back(temp_row);
            }
            row_count++;
        }
        return out;
    }
};
