#pragma once

#include "Matrix.h"
#include "AugmentedMatrix.h"
#include "Gauss.h"

namespace DLSES
{
    template <typename T>
    Matrix<T> eye(size_t n)
    {
        Matrix<T> result(n, n);

        for (size_t i = 0; i < n; i++)
            result(i, i) = 1;

        return result;
    }

    template <typename T>
    Matrix<T> inverse(const Matrix<T> &matrix)
    {
        if (matrix.nrow() != matrix.ncol())
            throw std::invalid_argument("Non quadratic matrix");

        auto m = matrix;
        auto inv = eye<T>(matrix.nrow());
        AugmentedMatrix<T> aug(m, inv);

        for (size_t i = 0; i < matrix.nrow(); i++)
        {
            if (m(i, i) == 0)
                throw std::invalid_argument("Non invertable matrix");

            gaussJordanEliminationStep(aug, i, i);
        }

        return inv;
    }

    template <typename T>
    T det(const Matrix<T> &matrix)
    {
        if (matrix.nrow() != matrix.ncol())
            throw std::invalid_argument("Non quadratic matrix");

        auto m = matrix;
        AugmentedMatrix<T> aug(m);
        T det = 1;

        for (size_t i = 0; i < matrix.nrow() - 1; i++)
        {
            auto max = i;
            for (size_t m = i + 1; m < matrix.nrow(); m++)
            {
                if (aug(m, i) > aug(max, i))
                    max = i;
            }
            if (max != i)
            {
                aug.swapRow(i, max);
                det = -1 * det;
            }

            det = det * aug(i, i);

            if (det == 0)
                return 0;

            gaussEliminationStep(aug, i, i);
        }
        det = det * aug(m.nrow() - 1, m.nrow() - 1);

        return det;
    }
}