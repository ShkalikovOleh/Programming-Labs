#pragma once
#include <vector>

#include "Matrix.h"
#include "Vector.h"
#include "AugmentedMatrix.h"
#include "Cholesky.h"
#include "GaussJordan.h"
#include "Substitution.h"

#ifdef PRINT
    #include "Utils.h"
#endif

namespace DLSES
{
    template <typename T, typename U>
    auto choleskySolve(const Matrix<T> &A, const Vector<U> &b)
    {
        auto chol = cholesky(A);
        auto y = forward(chol, b);
        auto x = backward(chol.transpose(), y);

#ifdef PRINT
        std::cout << "Cholesky solver y" << std::endl;
        print(y);
        std::cout << std::endl;
#endif

        return x;
    }

    template <typename T, typename U>
    auto ldlSolve(const Matrix<T> &A, const Vector<U> &b)
    {
        auto [l, d] = ldl(A);
        auto z = forward(l, b);

#ifdef PRINT
        std::cout << "LDL solver z" << std::endl;
        print(z);
        std::cout << std::endl;
#endif

        for (size_t i = 0; i < z.nval(); i++)
        {
            z(i) = z(i) / d(i);
        }

#ifdef PRINT
        std::cout << "LDL solver y" << std::endl;
        print(z);
        std::cout << std::endl;
#endif

        auto x = backward(l.transpose(), z);
        return x;
    }

    template <typename T>
    Vector<T> gaussJordanSolve(const Matrix<T> &A, const Vector<T> &b)
    {
        auto m = A;
        auto v = b;
        AugmentedMatrix<T> aug(m, v);
        for (int i = 0; i < m.nrow(); i++)
        {
            DLSES::gaussJordanEliminationStep(aug, i, i);

#ifdef PRINT
        std::cout << "Gauss Jordan solver. Step: " << i+1 << std::endl;
        std::cout << "Matrix A: " << std::endl;
        print(m);
        std::cout << "Vector b: " << std::endl;
        print(v);
#endif
        }

        return v;
    }
}
