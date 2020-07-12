#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
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
                                           std::function<T(T, T)> &binary_op) const
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

    std::vector<std::vector<T>> operator()(const std::vector<std::vector<T>> &data,
                                           T scalar,
                                           std::function<T(T, T)> binary_op) const
    {
        std::vector<std::vector<T>> out;
        out.reserve(data.size());
        std::transform(data.begin(),
                       data.end(),
                       std::back_inserter(out),
                       [&binary_op, scalar](const std::vector<T> &x1) {
                           std::vector<T> temp;
                           std::transform(x1.begin(),
                                          x1.end(),
                                          x1.begin(),
                                          std::back_inserter(temp),
                                          std::bind(binary_op, std::placeholders::_1, scalar));
                           return temp;
                       });
        return out;
    }
};