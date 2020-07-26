#pragma once
#include <vector>
#include "../customconcepts.hpp"

/**
 * @brief Matrix multiplies two matrix raw representations.
 * Expects that each raw representation can be used as a Matrix<T>.
 */
template <Number T>
class MatrixMultiplicatorRaw
{
public:
    std::vector<std::vector<T>> operator()(
        const std::vector<std::vector<T>> &left,
        const std::vector<std::vector<T>> &right)
    {
        std::vector<std::vector<T>> out;
        int n_cols = left.at(0).size();
        int out_rows = left.size();
        int out_cols = right.at(0).size();
        /** 
         * Again, I don't quite like this vector subsetting...
         * Alternatively, you can _transpose_ one of the matrices, multiply element-wise
         * two columns and then std::accumulate() them.
         * 
         * Or you can just implement Strassen or similar...
         */
        for (typename std::vector<T>::size_type i = 0; i < out_rows; ++i)
        {
            std::vector<T> temp_row;
            for (typename std::vector<T>::size_type j = 0; j < out_cols; ++j)
            {
                T temp_sum = T(0);
                for (typename std::vector<T>::size_type k = 0; k < n_cols; ++k)
                {
                    temp_sum += left[i][k] * right[k][j];
                }
                temp_row.push_back(temp_sum);
            }
            out.push_back(temp_row);
        }
        return out;
    }
};