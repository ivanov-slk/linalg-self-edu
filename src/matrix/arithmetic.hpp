#pragma once
#include <vector>
#include <algorithm>
#include <functional>

#include "../customconcepts.hpp"

/**
 * @brief Functor for doing arithmetic on matrix raw data.
 */
template <Number T>
class Arithmetic
{
public:
    std::vector<std::vector<T>> operator()(const std::vector<std::vector<T>> &left,
                                           const std::vector<std::vector<T>> &right,
                                           std::function<T(T, T)> &binary_op)
    {
        std::vector<std::vector<T>> out;
        out.reserve(left.size());
        std::transform(left.begin(),
                       left.end(),
                       right.begin(),
                       std::back_inserter(out),
                       [&binary_op](const std::vector<T> &x1,
                                    const std::vector<T> &x2) {
                           std::vector<T> temp;
                           std::transform(x1.begin(),
                                          x1.end(),
                                          x2.begin(),
                                          std::back_inserter(temp),
                                          binary_op);
                           return temp;
                       });
        return out;
    }
};