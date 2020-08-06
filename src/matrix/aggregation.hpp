#pragma once
#include <vector>
#include <numeric>
#include <ranges>
#include "../customconcepts.hpp"

/**
 * @brief Sums a matrix along a given axis.
 */
template <Number T>
class SumRaw
{
private:
    std::vector<std::vector<T>> sum_columns(std::vector<std::vector<T>> data)
    {
        std::vector<std::vector<T>> out;
        for (auto &row : data)
        {
            std::vector<T> temp_row;
            T row_sum = std::accumulate(row.begin(),
                row.end(),
                0);
            temp_row.push_back(row_sum);
            out.push_back(temp_row);
        }
        return out;
    }

    std::vector<std::vector<T>> sum_rows(std::vector<std::vector<T>> data)
    {
        std::vector<std::vector<T>> out;
        std::vector<T> sum_row;

        bool first = true;
        for (typename std::vector<std::vector<T>>::size_type i = 0; i < data.size(); ++i)
        {
            int counter = 0;
            for (typename std::vector<T>::size_type j = 0; j < data[i].size(); ++j)
            {
                if (first == true) {
                    sum_row.push_back(data[i][j]);
                }
                else {
                    sum_row.at(counter) += data[i][j];
                }
                ++counter;
            }
            first = false;
        }
        out.push_back(sum_row);
        return out;
    }

    std::vector<std::vector<T>> sum_all(std::vector<std::vector<T>> data)
    {
        std::vector<std::vector<T>> out;
        std::vector<T> sum_row;
        T total = T(0);
        for (auto &row : data)
        {
            for (auto &col : row)
            {
                total += col;
            }
        }
        sum_row.push_back(total);
        out.push_back(sum_row);
        return out;
    }

public:
    std::vector<std::vector<T>> operator()(std::vector<std::vector<T>> data, int axis)
    {
        if (axis == 0)
        {
            return sum_columns(data);
        }
        else if (axis == 1)
        {
            return sum_rows(data);
        }
        else if (axis == -1)
        {
            return sum_all(data);
        }
        std::vector<std::vector<T>> out;
        return out;
    }
};