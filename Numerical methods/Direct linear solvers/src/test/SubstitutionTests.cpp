#include <gtest/gtest.h>

#include "Matrix.h"
#include "Vector.h"
#include "Substitution.h"

using namespace DLSES;

TEST(SubstitutionTests, backward)
{
    Matrix<int> A(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 1) = 1;

    Vector<int> b(2);
    b(0) = 7;
    b(1) = 3;

    auto x = backward(A, b);

    EXPECT_EQ(x(0), 1);
    EXPECT_EQ(x(1), 3);
}

TEST(SubstitutionTests, backwardThrowIfDifferentShapes)
{
    Matrix<int> A1(2, 2);
    Matrix<int> A2(2, 3);
    Matrix<int> A3(3, 2);
    Vector<int> b(3);

    EXPECT_THROW(backward(A1, b), std::invalid_argument);
    EXPECT_THROW(backward(A2, b), std::invalid_argument);
    EXPECT_THROW(backward(A3, b), std::invalid_argument);
}

TEST(SubstitutionTests, forward)
{
    Matrix<int> A(2, 2);
    A(0, 0) = 1;
    A(1, 0) = 2;
    A(1, 1) = 1;

    Vector<int> b(2);
    b(0) = 3;
    b(1) = 7;

    auto x = forward(A, b);

    EXPECT_EQ(x(0), 3);
    EXPECT_EQ(x(1), 1);
}

TEST(SubstitutionTests, forwardThrowIfDifferentShapes)
{
    Matrix<int> A1(2, 2);
    Matrix<int> A2(2, 3);
    Matrix<int> A3(3, 2);
    Vector<int> b(3);

    EXPECT_THROW(forward(A1, b), std::invalid_argument);
    EXPECT_THROW(forward(A2, b), std::invalid_argument);
    EXPECT_THROW(forward(A3, b), std::invalid_argument);
}
