#pragma once
#include <cmath>
#include <concepts>
#include <functional>

#include "../exceptions.hpp"
#include "aggregation.hpp"
#include "arithmetic.hpp"
#include "multiplication.hpp"
#include "shapeutilities.hpp"
#include "transposition.hpp"

/**
 * @brief A matrix.
 */
template <Number T> class Matrix
{
  private:
    int n_rows = 0;
    int n_cols = 0;
    std::vector<std::vector<T>> data;
    // Just as an idea, consider flattening the representation.

    Matrix<T> do_arithmetic(const Matrix<T> &other, std::function<T(T, T)> binary_op) const
    {
        if (empty())
        {
            return Matrix<T>{other.data};
        }

        if (other.empty())
        {
            return Matrix<T>{data};
        }
        return Matrix<T>{Arithmetic<T>()(data, other.data, binary_op)};
    }

  public:
    Matrix()
    {
    }
    Matrix(const std::vector<std::vector<T>> &data) : data(data)
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
    bool empty() const
    {
        return data.empty();
    }

    /**
     * @brief Checks if two matrices are equal.
     * @param other Matrix
     * @return bool true if matrices are equal.
     *
     * ...should hash be also implemented?
     * ...should T be used again? What about different number template and cast?
     */
    bool equals(const Matrix<T> &other) const
    {
        return data == other.data;
    }

    /**
     * @brief Get the shape of the matrix
     *
     * @return std::pair<int, int> - `first` is the number of rows, `second` is the number of
     * columns
     */
    std::pair<int, int> get_shape() const
    {
        return std::make_pair(n_rows, n_cols);
    }

    /**
     * @brief Get the raw data.
     */
    std::vector<std::vector<T>> get_data() const
    {
        return data;
    }

    /**
     * @brief Add a matrix to this.
     */
    Matrix<T> add(const Matrix<T> &other) const
    {
        return do_arithmetic(other, std::plus<T>());
    }

    /**
     * @brief Add a scalar to each element of this.
     */
    Matrix<T> add(T scalar) const
    {
        return Matrix<T>{Arithmetic<T>()(data, scalar, std::plus<T>())};
    }

    /**
     * @brief Subtract a matrix from this.
     */
    Matrix<T> subtract(const Matrix<T> &other) const
    {
        return do_arithmetic(other, std::minus<T>());
    }

    /**
     * @brief Subtract a scalar from each element of this.
     */
    Matrix<T> subtract(T scalar) const
    {
        return Matrix<T>{Arithmetic<T>()(data, scalar, std::minus<T>())};
    }

    /**
     * @brief Multiply a matrix by this elementwise.
     */
    Matrix<T> el_multiply(const Matrix<T> &other) const
    {
        return do_arithmetic(other, std::multiplies<T>());
    }

    /**
     * @brief Multiply a matrix by a scalar.
     */
    Matrix<T> el_multiply(T scalar) const
    {
        return Matrix<T>{Arithmetic<T>()(data, scalar, std::multiplies<T>())};
    }

    /**
     * @brief Divide this by other.
     */
    Matrix<T> el_divide(const Matrix<T> &other) const
    {
        return do_arithmetic(other, std::divides<T>());
    }

    /**
     * @brief Divide each element of this by a scalar.
     */
    Matrix<T> el_divide(T scalar) const
    {
        return Matrix<T>{Arithmetic<T>()(data, scalar, std::divides<T>())};
    }

    /**
     * @brief Sums a matrix along a given axis. If -1 is supplied,
     * the total sum is returned. Optionally, each matrix element can
     * be raised to `power` before summing.
     */
    Matrix<T> sum(int axis, T power)
    {
        return Matrix<T>{SumRaw<T>()(data, axis, power)};
    }

    /**
     * @brief Return new transposed matrix.
     */
    Matrix<T> transpose() const
    {
        return Matrix<T>{Transposer<T>()(data, get_shape())};
    }

    /**
     * @brief Multiplies two matrices producing new one.
     */
    Matrix<T> multiply(const Matrix<T> &other) const
    {
        if (empty())
        {
            return Matrix<T>{other.data};
        }

        if (other.empty())
        {
            return Matrix<T>{data};
        }

        if (get_shape().second != other.get_shape().first)
        {
            throw BadDimensionsException("The dimensions are invalid for matrix multiplication.");
        }
        return Matrix<T>{MatrixMultiplicatorRaw<T>()(data, other.data)};
    }

    // Not implemented because of circular includes. Use MatrixInverter<T> directly instead.
    // /**
    //  * @brief Invert a matrix. Currently implemented only for symmetric matrices via
    //  eigendecomosition.
    //  */
    // Matrix<T>
    // invert()
    // {

    //     Matrix<T> out;
    //     return MatrixInverter<T>()(this);
    // }

    /**
     * @brief Take the norm of the matrix.
     *
     * Note that if the matrix has only one row / column, the vector norm is returned.
     * Otherwise, the "entrywise" norm of the whole matrix is returned. For p=2,
     * this is the Frobenius norm.
     *
     * Check https://en.wikipedia.org/wiki/Matrix_norm#%22Entrywise%22_matrix_norms.
     */
    T norm(T p) const
    {
        T temp_sum = T(0);
        for (typename std::vector<T>::size_type i = 0; i < n_rows; ++i)
        {
            for (typename std::vector<T>::size_type j = 0; j < n_cols; ++j)
            {
                // explicit casting, the norm is unlikely to be an integer
                T current_value = data[i][j];
                // take absolute value (might use std::abs(), but have to manage overloads)
                // then exponentiate
                temp_sum += std::pow(((current_value < 0) ? -current_value : current_value), p);
            }
        }
        return std::pow(temp_sum, (1 / p));
    }

    /**
     * @brief Find the trace of the matrix.
     *
     * Works only for square matrices. Otherwise returns 0.
     * ?? Is it ok to return 0? Why not raise an exception?
     */
    T trace() const
    {
        if (n_rows != n_cols)
        {
            return T(0);
        }
        T temp_sum = T(0);
        for (typename std::vector<T>::size_type i = 0; i < n_rows; ++i)
        {
            temp_sum += data[i][i];
        }
        return temp_sum;
    }

    /**
     * @brief Sets an element to a value.
     */
    void set_element(T value, int row, int col)
    {
        if ((row > n_rows - 1) || (col > n_cols - 1))
        {
            throw BadDimensionsException("The requested element doesn't exist.");
        }
        data.at(row).at(col) = value;
    }

    /**
     * @brief Extracts an element from this.
     *
     * @return The requested element.
     */
    T extract_element(int row, int col) const
    {
        if ((row > n_rows - 1) || (col > n_cols - 1))
        {
            throw BadDimensionsException("The requested element doesn't exist.");
        }
        return ExtractElementRaw<T>()(data, row, col);
    }

    /**
     * @brief Extracts a row from this.
     *
     * @return A matrix representing the requested row of this.
     */
    Matrix<T> extract_row(int row) const
    {
        if (row > n_rows - 1)
        {
            throw BadDimensionsException(
                "The requested row does not exist. This matrix is smaller.");
        }
        return Matrix<T>{ExtractRowRaw<T>()(data, row)};
    }

    /**
     * @brief Extracts a column from this.
     *
     * @return A matrix representing the requested column of this.
     */
    Matrix<T> extract_column(int col) const
    {
        if (col > n_cols - 1)
        {
            throw BadDimensionsException(
                "The requested column does not exist. This matrix is smaller.");
        }
        return Matrix<T>{ExtractColumnRaw<T>()(data, col)};
    }

    // /**
    //  * @brief Extracts an adjoint matrix from this.
    //  * @param int row: The row to remove. Negative to not remove anything. Starts at zero.
    //  * @param int col: The column to remove. Negative to not remove anything. Starts at zero.
    //  * @return A matrix without the given row and/or column of this.
    //  */
    // Matrix<T> extract_without(int row, int col) const
    // {
    //     if ((row > n_rows - 1) || (col > n_cols - 1))
    //     {
    //         throw BadDimensionsException("The requested row / column doesn't exist.");
    //     }
    //     return Matrix<T>{ExtractSubmatrixRaw<T>()(data, row, col, std::not_equal_to<T>())};
    // }

    /**
     * @brief Extracts a submatrix from this.
     * @param int row: The row to remove. Negative to not remove anything. Zero-indexed.
     * @param int col: The column to remove. Negative to not remove anything. Zero-indexed.
     * @param std::function<T(T, T)> row_comparison_op: Comparison function object
     * @param std::function<T(T, T)> col_comparison_op: Comparison function object
     * @return A matrix representing the requested submatrix of this.
     */
    Matrix<T> extract_submatrix(int row, int col, std::function<T(T, T)> row_comparison_op,
                                std::function<T(T, T)> col_comparison_op) const
    {
        // row and col must be nonnegative and less than n_rows / n_cols respectively
        if (((row > n_rows) || (col > n_cols)) || ((row < 0) || (col < 0)))
        {
            throw BadDimensionsException("The requested row / column doesn't exist.");
        }

        // std::function<T(T, T)> comparison_op;
        // if (comparison_type == "equal_to")
        // {
        //     comparison_op = std::equal_to<T>();
        // }
        // else if (comparison_type == "not_equal_to")
        // {
        //     comparison_op = std::not_equal_to<T>();
        // }
        // else if (comparison_type == "greater")
        // {
        //     comparison_op = std::greater<T>();
        // }
        // else if (comparison_type == "less")
        // {
        //     comparison_op = std::less<T>();
        // }
        // else if (comparison_type == "greater_equal")
        // {
        //     comparison_op = std::greater_equal<T>();
        // }
        // else if (comparison_type == "less_equal")
        // {
        //     comparison_op = std::less_equal<T>();
        // }
        // else
        // {
        //     throw InvalidComparisonTypeException("The requested comparison type is not
        //     supported.");
        // }
        return Matrix<T>{
            ExtractSubmatrixRaw<T>()(data, row, col, row_comparison_op, col_comparison_op)};
    }

    /**
     * @brief Checks if the matrix is symmetric.
     *
     * Relies on the property that A = A^T.
     */
    bool is_symmetric() const
    {
        return this->equals(transpose());
    }

    /**
     * @brief Check if the matrix is diagonal.
     *
     * Consider refactoring.
     */
    bool is_diagonal() const
    {
        for (int i = 0; i < n_rows; ++i)
        {
            for (int j = 0; j < n_cols; ++j)
            {
                if ((i != j) & (data[i][j] != T(0)))
                {
                    return false;
                }
            }
        }
        return true;
    }

    void print_repr()
    {
        for (auto &row : data)
        {
            for (auto &col : row)
            {
                std::cout << "| " << col << " ";
            }
            std::cout << "|\n";
        }
        std::cout << '\n';
    }
};

template <Number T> bool operator==(const Matrix<T> lhs, const Matrix<T> rhs)
{
    return lhs.equals(rhs);
}
