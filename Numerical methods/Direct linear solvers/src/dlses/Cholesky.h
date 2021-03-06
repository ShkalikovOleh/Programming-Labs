#pragma once

#include <cmath>
#include <tuple>
#include "Matrix.h"

#ifdef PRINT
    #include "Utils.h"
#endif

namespace DLSES
{
    template <typename T>
    auto cholesky(const Matrix<T> &matrix)
    {
        if(!matrix.isSymmetric())
            throw std::invalid_argument("Matrix does not symmetric");

        using ret_type = decltype(std::sqrt(std::declval<T>()));
        Matrix<ret_type> result(matrix.nrow(), matrix.ncol());

        for (size_t i = 0; i < matrix.nrow(); i++)
        {
            for (size_t j = 0; j <= i; j++)
            {
                ret_type sum = 0;
                for(size_t k = 0; k < j; k++)
                {
                    sum += result(i, k) * result(j, k);
                }

                if (j == i)
                    result(i,i) = std::sqrt(matrix(i,i) - sum);
                else
                    result(i,j) = (matrix(i,j) - sum) / result(j,j);
            }

#ifdef PRINT
            std::cout << "Cholesky decomposition. Step: " << i+1 << std::endl;
            print(result);
            std::cout << std::endl;
#endif
        }

        return result;
    }

    template <typename T>
    auto ldl(const Matrix<T> &matrix)
    {
        if(!matrix.isSymmetric())
            throw std::invalid_argument("Matrix does not symmetric");

        using ret_type = decltype(std::sqrt(std::declval<T>())); //??? problem: int / int -> int
        Matrix<ret_type> l(matrix.nrow(), matrix.ncol());
        Vector<ret_type> d(matrix.nrow());

        for (size_t i = 0; i < matrix.nrow(); i++)
        {
            for (size_t j = 0; j <= i; j++)
            {
                ret_type sum = 0;
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

#ifdef PRINT
            std::cout << "LDL decomposition. Step: " << i+1 << std::endl;
            std::cout << "L:" << std::endl;
            print(l);
            std::cout << std::endl;
            std::cout << "D:" << std::endl;
            print(d);
            std::cout << std::endl;
#endif
        }

        return std::make_tuple(l, d);
    }
}
