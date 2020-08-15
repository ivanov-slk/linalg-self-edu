#pragma once
#include "../customconcepts.hpp"
#include <vector>

/**
 * @brief Transpose a matrix raw representation.
 */
template <Number T> class Transposer
{
  public:
    std::vector<std::vector<T>> operator()(const std::vector<std::vector<T>> &data,
                                           const std::pair<int, int> &shape)
    {
        // consider a better implementation...
        std::vector<std::vector<T>> out;
        for (typename std::vector<T>::size_type i = 0; i < shape.second; ++i)
        {
            std::vector<T> temp;
            for (typename std::vector<T>::size_type j = 0; j < shape.first; ++j)
            {
                temp.push_back(data[j][i]);
            }
            out.push_back(temp);
        }
        return out;
    }
};