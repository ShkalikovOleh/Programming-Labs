#pragma once

#include <cmath>
#include "Matrix.h"
#include "MatrixView.h"
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
    Matrix<T> inverse(Matrix<T> matrix)
    {
        if (matrix.nrow() != matrix.ncol())
            throw std::invalid_argument("Non quadratic matrix");

        auto inv = eye<T>(matrix.nrow());
        MatrixMatrixView<T> aug(matrix, inv);

        for (size_t i = 0; i < matrix.nrow(); i++)
        {
            if (matrix(i, i) == 0)
                throw std::invalid_argument("Non invertable matrix");

            gaussJordanEliminationStep(aug, i, i);
        }

        return inv;
    }

    template <typename T>
    T det(Matrix<T> matrix)
    {
        if (matrix.nrow() != matrix.ncol())
            throw std::invalid_argument("Non quadratic matrix");

        MatrixView<T> aug(matrix);
        T det = 1;

        for (size_t i = 0; i < matrix.nrow() - 1; i++)
        {
            auto max = i;
            for (size_t m = i + 1; m < matrix.nrow(); m++)
            {
                if (std::abs(aug(m, i)) > std::abs(aug(max, i)))
                    max = m;
            }
            if (max != i)
            {
                aug.swapRows(i, max);
                det = -1 * det;
            }

            det = det * aug(i, i);

            if (det == 0)
                return 0;

            gaussEliminationStep(aug, i, i);
        }
        det = det * aug(matrix.nrow() - 1, matrix.nrow() - 1);

        return det;
    }
}