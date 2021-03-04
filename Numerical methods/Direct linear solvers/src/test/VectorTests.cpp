#include <gtest/gtest.h>
#include <cmath>

#include "Vector.h"

using namespace DLSES;

class VectorTests : public ::testing::Test
{
protected:
    void SetUp() override
    {
        vector = new Vector<int>(2);
        (*vector)(0) = 1;
        (*vector)(1) = 2;
    }

    void TearDown() override
    {
        delete vector;
    }

    Vector<int> *vector;
};

TEST_F(VectorTests, nval)
{
    auto vec = *vector;

    ASSERT_EQ(vec.nval(), 2);
}

TEST_F(VectorTests, norm)
{
    auto vec = *vector;

    ASSERT_DOUBLE_EQ(vec.norm(), std::sqrt(5));
}

TEST_F(VectorTests, sum)
{
    auto vec = *vector;

    auto sum = vec + vec;

    EXPECT_EQ(sum.nval(), vec.nval());
    for (int i = 0; i < sum.nval(); i++)
    {
        EXPECT_EQ(sum(i), 2*vec(i));
    }
}

TEST_F(VectorTests, substract)
{
    auto vec = *vector;

    auto sum = vec - vec;

    EXPECT_EQ(sum.nval(), vec.nval());
    for (int i = 0; i < sum.nval(); i++)
    {
        EXPECT_EQ(sum(i), 0);
    }
}