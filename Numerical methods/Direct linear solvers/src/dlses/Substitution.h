#pragma once

#include "Matrix.h"
#include "Vector.h"

namespace DLSES
{
    template <typename T, typename U>
    auto forward(const IMatrix<T> &A, const Vector<U> &b)
    {
        if (A.nrow() != b.nval() || A.ncol() != b.nval())
            throw std::invalid_argument("Invalid sizes");

        Vector<typename std::common_type<T, U>::type> x(b.nval());

        for (size_t i = 0; i < A.nrow(); i++)
        {
            T sum = 0;
            for (size_t j = 0; j < i; j++)
            {
                sum += A(i, j) * x(j);
            }
            x(i) = (b(i) - sum) / A(i, i);
        }

        return x;
    }

    template <typename T, typename U>
    auto backward(const IMatrix<T> &A, const Vector<U> &b)
    {
        // if (A.nrow() != b.nval() || A.ncol() != b.nval())
        //     throw std::invalid_argument("Invalid sizes");

        Vector<typename std::common_type<T, U>::type> x(b.nval());

        size_t i = A.nrow();
        do
        {
            i--;
            T sum = 0;
            for (size_t j = i + 1; j < A.nrow(); j++)
            {
                sum += A(i, j) * x(j);
            }
            x(i) = (b(i) - sum) / A(i, i);
        } while (i != 0);

        return x;
    }
}
