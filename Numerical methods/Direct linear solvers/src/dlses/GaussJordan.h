#pragma once

#include "AugmentedMatrix.h"

namespace DLSES
{
    template <typename T>
    void gaussJordanEliminationStep(AugmentedMatrix<T>& matrix, size_t i, size_t j)
    {
        for (size_t k = 0; k < matrix.nrow(); k++)
        {
            auto pivot = matrix(i, j);
            auto mult = matrix(k, j) / pivot;
            for (size_t l = 0; l < matrix.ncol(); l++)
            {
                if (i == k)
                    matrix(k, l) = matrix(k, l) / pivot;
                else if (j == l)
                    matrix(k, l) = 0;
                else
                    matrix(k, l) = matrix(k, l) - mult * matrix(i, l);
            }
        }
    }
}