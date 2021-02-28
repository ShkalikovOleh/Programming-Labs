#pragma once

#include <cmath>
#include <tuple>
#include "Matrix.h"

namespace DLSES
{
    template <typename T>
    Matrix<T> cholesky(const Matrix<T> &matrix)
    {
        if(!matrix.isSymmetric())
            throw std::invalid_argument("Matrix does not symmetric");

        Matrix<T> result(matrix.nrow(), matrix.ncol());

        for (size_t i = 0; i < matrix.nrow(); i++)
        {
            for (size_t j = 0; j <= i; j++)
            {
                T sum = 0;
                for(size_t k = 0; k < j; k++)
                {
                    sum += result(i, k) * result(j, k);
                }

                if (j == i)
                    result(i,i) = std::sqrt(matrix(i,i) - sum);
                else
                    result(i,j) = (matrix(i,j) - sum) / result(j,j);
            }
        }

        return result;
    }

    template <typename T>
    auto ldl(const Matrix<T> &matrix)
    {
        if(!matrix.isSymmetric())
            throw std::invalid_argument("Matrix does not symmetric");

        Matrix<T> l(matrix.nrow(), matrix.ncol());
        Vector<T> d(matrix.nrow());

        for (size_t i = 0; i < matrix.nrow(); i++)
        {
            for (size_t j = 0; j <= i; j++)
            {
                T sum = 0;
                for(size_t k = 0; k < j; k++)
                {
                    sum += l(i, k) * l(j, k) * d(k);
                }

                if (j == i)
                {
                    l(i, i) = 1;
                    d(i) = matrix(i,i) - sum;
                }
                else
                {
                    l(i,j) = (matrix(i,j) - sum) / d(j);
                }
            }
        }

        return std::make_tuple(l, d);
    }
}
