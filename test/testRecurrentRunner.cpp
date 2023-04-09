#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "RecurrentRunner.hpp"
#include "types.hpp"
#include "IntervalLessThanZero.hpp"

using namespace testing;


class TestRecurrentRunner : public ::testing::Test
{
protected:
    MockFunction<void(void)> mockCallback;
    const std::chrono::milliseconds interval{1};
};

TEST_F(TestRecurrentRunner, givenRecurrent_whenRunIsCalledWithMinus1MillisecondsTimeToCall_thenExpectThrow)
{
    RecurrentRunner<> recurrentRunner{};
    EXPECT_THROW({
        recurrentRunner.run([]{}, std::chrono::milliseconds{-1});
    }, IntervalLessThanZero);    
}