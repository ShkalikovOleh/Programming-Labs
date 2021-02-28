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
}
