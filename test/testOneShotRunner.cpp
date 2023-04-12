#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "OneShotRunner.hpp"
#include "types.hpp"
#include "IntervalLessThanZero.hpp"

using namespace testing;


class TestOneShotRunner : public ::testing::Test
{
protected:
    MockFunction<void(void)> mockCallback;
    const milliseconds interval{1};
};

TEST_F(TestOneShotRunner, givenOneShotRunner_whenRunIsCalled_thenExpectCallCallback)
{
    EXPECT_CALL(mockCallback, Call());

    OneShotRunner oneShotRunner{};
    oneShotRunner.run(mockCallback.AsStdFunction(), interval);
}

TEST_F(TestOneShotRunner, givenOneShotRunner_whenRunIsCalledWithMinus1MillisecondsTimeToCall_thenExpectThrow)
{
    OneShotRunner oneShotRunner{};
    EXPECT_THROW({
        oneShotRunner.run([]{}, {-1});
    }, IntervalLessThanZero);    
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
