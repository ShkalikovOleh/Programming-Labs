#pragma once
#include <vector>

#include "Matrix.h"
#include "Vector.h"
#include "Cholesky.h"
#include "Substitution.h"

namespace DLSES
{
    template <typename T, typename U>
    auto choleskySolve(const Matrix<T> &A, const Vector<U> &b)
    {
        auto chol = cholesky(A);
        auto z = forward(chol, b);
        auto x = backward(chol.transpose(), z);
        return x;
    }

    template <typename T, typename U>
    auto ldlSolve(const Matrix<T> &A, const Vector<U> &b)
    {
        auto [l, d] = ldl(A);
        auto z = forward(l, b);

        for (size_t i = 0; i < z.nval(); i++)
        {
            z(i) = z(i) / d(i);
        }

        auto x = backward(l.transpose(), z);
        return x;
    }
}
