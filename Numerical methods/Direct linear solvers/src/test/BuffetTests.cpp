#include <gtest/gtest.h>
#include <cmath>

#include "Buffer.h"

using namespace DLSES;

class BufferTests : public ::testing::Test
{
protected:
    void SetUp() override
    {
        buffer = new Buffer<int>(2);
        (*buffer)[0] = 1;
        (*buffer)[1] = 2;
    }

    void TearDown() override
    {
        delete buffer;
    }

    Buffer<int> *buffer;
};

TEST_F(BufferTests, copyCtor)
{
    auto buff = *buffer;

    Buffer<int> copy(buff);
    copy[0] += 1;

    EXPECT_NE(copy[0], buff[0]);
}

TEST_F(BufferTests, copyAssigment)
{
    auto buff = *buffer;

    Buffer<int> copy = buff;
    copy[0] += 1;

    EXPECT_NE(copy[0], buff[0]);
}

TEST_F(BufferTests, moveCtor)
{
    auto buff = *buffer;
    auto first = &buff[0];

    Buffer<int> moved(std::move(buff));

    EXPECT_EQ(buff.size(), 0);
    EXPECT_EQ(&moved[0], first);
}

TEST_F(BufferTests, moveAssigment)
{
    auto buff = *buffer;
    auto first = &buff[0];

    Buffer<int> moved = std::move(buff);

    EXPECT_EQ(buff.size(), 0);
    EXPECT_EQ(&moved[0], first);
}
