#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include "../customconcepts.hpp"

/**
 * @brief Sums a matrix along a given axis. 
 */
template <Number T>
class SumRaw
{
public:
    std::vector<std::vector<T>> operator()(std::vector<std::vector<T>> data, int axis)
    {
        std::vector<std::vector<T>> out;
        for (auto &row : data)
        {
            std::vector<T> temp_row;
            T temp_sum = 0;
            for (auto &el : row)
            {
                temp_sum += el;
            }
            temp_row.push_back(el);
        }
    }
};