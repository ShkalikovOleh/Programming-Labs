#include <gtest/gtest.h>

#include "Matrix.h"
#include "Vector.h"

using namespace DLSES;

class MatrixTests : public ::testing::Test
{
protected:
    void SetUp() override
    {
        matrix = new Matrix<int>(2, 2);
        (*matrix)(0, 0) = 1;
        (*matrix)(0, 1) = 2;
        (*matrix)(1, 0) = 3;
        (*matrix)(1, 1) = 4;
    }

    void TearDown() override
    {
        delete matrix;
    }

    Matrix<int> *matrix;
};

TEST_F(MatrixTests, shape)
{
    auto mat = *matrix;

    EXPECT_EQ(mat.nrow(), 2);
    EXPECT_EQ(mat.ncol(), 2);
}

TEST_F(MatrixTests, transpose)
{
    auto mat = *matrix;
    auto result = mat.transpose();

    EXPECT_EQ(result.ncol(), mat.ncol());
    EXPECT_EQ(result.nrow(), mat.nrow());

    for (int i = 0; i < mat.nrow(); i++)
    {
        for (int j = 0; j < mat.ncol(); j++)
        {
            EXPECT_EQ(result(i, j), mat(j, i));
        }
    }
}

TEST_F(MatrixTests, isNotSymmetric)
{
    auto mat = *matrix;

    ASSERT_FALSE(mat.isSymmetric());
}

TEST_F(MatrixTests, isSymmetric)
{
    Matrix<int> mat(2, 2);
    mat(0, 0) = 1;
    mat(1, 1) = 2;
    mat(0, 1) = mat(1, 0) = 3;

    ASSERT_TRUE(mat.isSymmetric());
}

TEST_F(MatrixTests, multMatrix)
{
    auto mat = *matrix;

    auto prod = mat * mat;

    EXPECT_EQ(prod(0, 0), 7);
    EXPECT_EQ(prod(0, 1), 10);
    EXPECT_EQ(prod(1, 0), 15);
    EXPECT_EQ(prod(1, 1), 22);
}

TEST_F(MatrixTests, multVector)
{
    auto mat = *matrix;
    Vector<int> vec(2);
    vec(0) = 1;
    vec(1) = 2;

    auto prod = mat * vec;

    EXPECT_EQ(prod(0), 5);
    EXPECT_EQ(prod(1), 11);
}