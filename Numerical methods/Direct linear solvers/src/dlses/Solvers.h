#pragma once
#include <vector>

#include "Matrix.h"
#include "Vector.h"
#include "AugmentedMatrix.h"
#include "Cholesky.h"
#include "Gauss.h"
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

        template <typename T, typename U>
        auto gaussJordanSolve(const Matrix<T> &A, const Vector<U> &b)
        {
                using ret_type = typename std::common_type<T, U>::type;
                Matrix<ret_type> m(A);
                Vector<ret_type> v(b);
                AugmentedMatrix<ret_type> aug(m, v);

                for (size_t i = 0; i < m.nrow(); i++)
                {
                        DLSES::gaussJordanEliminationStep(aug, i, i);

#ifdef PRINT
                        std::cout << "Gauss Jordan solver. Step: " << i + 1 << std::endl;
                        std::cout << "Matrix A: " << std::endl;
                        print(m);
                        std::cout << "Vector b: " << std::endl;
                        print(v);
#endif
                }

                return v;
        }

        template <typename T, typename U>
        auto gaussPivotSolve(const Matrix<T> &A, const Vector<U> &b)
        {
                using ret_type = typename std::common_type<T, U>::type;
                Matrix<ret_type> m(A);
                Vector<ret_type> v(b);
                AugmentedMatrix<ret_type> aug(m, v);
                aug.swapRow(0, 3);

                for (size_t i = 0; i < m.nrow(); i++)
                {
                        DLSES::gaussEliminationStep(aug, i, i);

#ifdef PRINT
                        std::cout << "Gauss Jordan solver. Step: " << i + 1 << std::endl;
                        std::cout << "Matrix A: " << std::endl;
                        print(m);
                        std::cout << "Vector b: " << std::endl;
                        print(v);
#endif
                }

                auto x = backward(m, v);
                return x;
        }
}
