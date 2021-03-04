#include <gtest/gtest.h>

#include "Matrix.h"
#include "Vector.h"
#include "Cholesky.h"

using namespace DLSES;

Matrix<int> testMatrix()
{
    //Example from: https://en.wikipedia.org/wiki/Cholesky_decomposition
    Matrix<int> matrix(3, 3);
    matrix(0, 0) = 4;
    matrix(0, 1) = matrix(1, 0) = 12;
    matrix(0, 2) = matrix(2, 0) = -16;
    matrix(1, 1) = 37;
    matrix(1, 2) = matrix(2, 1) = -43;
    matrix(2, 2) = 98;

    return matrix;
}

TEST(CholeskyTests, cholesky)
{
    auto matrix = testMatrix();

    auto l = cholesky(matrix);

    EXPECT_EQ(l.nrow(), matrix.nrow());
    EXPECT_EQ(l.ncol(), l.nrow());

    EXPECT_EQ(l(0, 0), 2);
    EXPECT_EQ(l(1, 0), 6);
    EXPECT_EQ(l(1, 1), 1);
    EXPECT_EQ(l(2, 0), -8);
    EXPECT_EQ(l(2, 1), 5);
    EXPECT_EQ(l(2, 2), 3);

    for (int i = 0; i < l.nrow(); i++)
    {
        for (int j = i + 1; j < l.ncol(); j++)
        {
            EXPECT_EQ(l(i, j), 0);
        }
    }
}

TEST(CholeskyTests, choleskyThrowIfNonQuadratic)
{
    Matrix<int> matrix(2, 3);

    ASSERT_THROW(cholesky(matrix), std::invalid_argument);
}

TEST(CholeskyTests, choleskyThrowIfNonSymmetric)
{
    Matrix<int> matrix(2, 2);
    matrix(0,1) = 1;

    ASSERT_THROW(cholesky(matrix), std::invalid_argument);
}

TEST(CholeskyTests, ldl)
{
    auto matrix = testMatrix();

    auto [l, d] = ldl(matrix);

    EXPECT_EQ(l.nrow(), matrix.nrow());
    EXPECT_EQ(l.ncol(), l.nrow());
    EXPECT_EQ(d.nval(), matrix.nrow());

    EXPECT_EQ(d(0), 4);
    EXPECT_EQ(d(1), 1);
    EXPECT_EQ(d(2), 9);

    EXPECT_EQ(l(0, 0), 1);
    EXPECT_EQ(l(1, 0), 3);
    EXPECT_EQ(l(1, 1), 1);
    EXPECT_EQ(l(2, 0), -4);
    EXPECT_EQ(l(2, 1), 5);
    EXPECT_EQ(l(2, 2), 1);

    for (int i = 0; i < l.nrow(); i++)
    {
        for (int j = i + 1; j < l.ncol(); j++)
        {
            EXPECT_EQ(l(i, j), 0);
        }
    }
}

TEST(CholeskyTests, ldlThrowIfNonQuadratic)
{
    Matrix<int> matrix(2, 3);

    ASSERT_THROW(ldl(matrix), std::invalid_argument);
}

TEST(CholeskyTests, ldlThrowIfNonSymmetric)
{
    Matrix<int> matrix(2, 2);
    matrix(0,1) = 1;

    ASSERT_THROW(ldl(matrix), std::invalid_argument);
}
