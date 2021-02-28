#pragma once

#include "Matrix.h"
#include "Vector.h"
#include "Cholecky.h"
#include "Substitution.h"

namespace DLSES
{
    template <typename T>
    Vector<T> choleckySolve(const Matrix<T> &A, const Vector<T> &b)
    {
        auto chol = cholesky(A);
        auto z = forward(chol, b);
        auto x = backward(chol.transpose(), z);
        return x;
    }

    template <typename T>
    Vector<T> ldlSolve(const Matrix<T> &A, const Vector<T> &b)
    {
        auto [l, d] = ldl(A);
        auto z = forward(l, b);

        Vector<T> y(z.nval());
        for (size_t i = 0; i < z.nval(); i++)
        {
            y(i) = z(i) / d(i);
        }

        auto x = backward(l.transpose(), y);
        return x;
    }
}
