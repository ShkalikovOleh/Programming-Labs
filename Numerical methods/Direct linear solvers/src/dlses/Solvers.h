#pragma once
#include <vector>

#include "Matrix.h"
#include "Vector.h"
#include "MatrixView.h"
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
                auto x = backward(TransposeView(chol), y);

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

                auto x = backward(TransposeView(l), z);
                return x;
        }

        template <typename T, typename U>
        auto gaussJordanSolve(const Matrix<T> &A, const Vector<U> &b)
        {
                using ret_type = typename std::common_type<T, U>::type;
                Matrix<ret_type> m(A);
                Vector<ret_type> v(b);
                MatrixVectorView<ret_type> aug(m, v);

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
        auto gaussSolve(const Matrix<T> &A, const Vector<U> &b)
        {
                using ret_type = typename std::common_type<T, U>::type;
                Matrix<ret_type> m(A);
                Vector<ret_type> v(b);
                MatrixVectorView<ret_type> aug(m, v);

                for (size_t i = 0; i < m.nrow(); i++)
                {
                        DLSES::gaussEliminationStep(aug, i, i);

#ifdef PRINT
                        std::cout << "Gauss solver. Step: " << i + 1 << std::endl;
                        std::cout << "Matrix A: " << std::endl;
                        print(m);
                        std::cout << "Vector b: " << std::endl;
                        print(v);
#endif
                }

                auto x = backward(m, v);

                return x;
        }

        template <typename T, typename U>
        auto gaussPivotSolve(const Matrix<T> &A, const Vector<U> &b)
        {
                using ret_type = typename std::common_type<T, U>::type;
                Matrix<ret_type> m(A);
                Vector<ret_type> v(b);
                MatrixVectorView<ret_type> aug(m, v);

                for (size_t i = 0; i < m.nrow(); i++)
                {
                        auto max = i;
                        for (size_t l = i + 1; l < m.nrow(); l++)
                        {
                            if (std::abs(aug(l, i)) > std::abs(aug(max, i)))
                                max = l;
                        }
                        if (max != i)
                        {
                            aug.swapRows(i, max);
                        }

                        DLSES::gaussEliminationStep(aug, i, i);

#ifdef PRINT
                        std::cout << "Gauss with pivoting solver. Step: " << i + 1 << std::endl;
                        std::cout << "Matrix A: " << std::endl;
                        print(m);
                        std::cout << "Vector b: " << std::endl;
                        print(v);
#endif
                }

                size_t i = A.nrow();
                Vector<ret_type> res(b.nval());
                do
                {
                    i--;
                    T sum = 0;
                    for (size_t j = i + 1; j < A.nrow(); j++)
                    {
                        sum += aug(i, j) * res(j);
                    }
                    res(i) = (aug(i, A.ncol()) - sum) / aug(i, i);
                } while (i != 0);

                return res;
        }
}
