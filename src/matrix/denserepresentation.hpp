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

    /**
     * @brief Checks if the matrix is empty.
     * @return bool true if the matrix is empty.
     */
    bool empty() const { return data.empty(); }

    /**
     * @brief Get the shape of the matrix
     * 
     * @return std::pair<int, int> - `first` is the number of rows, `second` is the number of columns
     */
    std::pair<int, int> get_shape() { return std::make_pair(n_rows, n_cols); }
};