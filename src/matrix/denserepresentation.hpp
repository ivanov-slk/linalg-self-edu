#pragma once
#include "../customconcepts.hpp"
#include "../exceptions.hpp"

/**
 * @brief A dense representation for a matrix.
 */
template <Number T>
class DenseRepresentation
{
private:
    int n_cols = 0;
    int n_rows = 0;
    std::vector<std::vector<T>> data;

public:
    DenseRepresentation() {}
    DenseRepresentation(const std::vector<std::vector<T>> &data) : data(data)
    {
        if (data.empty())
        {
            n_rows = 0;
            n_cols = 0;
        }
        else
        {
            n_rows = data.size();
            int temp_cols = data[0].size();
            for (std::vector<T> element : data)
            {
                if (element.size() != temp_cols)
                {
                    throw BadDimensionsException("Each row must have the same number of elements.");
                }
                temp_cols = element.size();
            }
            n_cols = temp_cols;
        }
    }
    bool empty() const { return data.empty(); }
};