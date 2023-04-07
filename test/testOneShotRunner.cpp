#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "OneShotRunner.hpp"
#include "types.hpp"

using namespace testing;


class TestOneShotRunner : public ::testing::Test
{
protected:
    MockFunction<void(void)> mockCallback;
    const std::chrono::milliseconds interval{1};
};

TEST_F(TestOneShotRunner, givenTimerWithOneShotRunner_whenStartIsCalled_thenExpectCallCallback)
{
    EXPECT_CALL(mockCallback, Call());

    OneShotRunner<> oneShotRunner{};
    oneShotRunner.run(mockCallback.AsStdFunction(), interval);
}

TEST_F(TestOneShotRunner, givenTimerWithOneShotRunnerWithArgs_whenStartIsCalled_thenExpectCallCallback)
{
    MockFunction<void(const int, const int)> mockCallbackWithArgs;
    const  int firstArgument=1;
    const  int secondArgument=2;
    EXPECT_CALL(mockCallbackWithArgs, Call(1, 2));

    OneShotRunner<std::chrono::milliseconds, std::function<void(const int, const int)>, const int, const int> oneShotRunner{};
    oneShotRunner.run(mockCallbackWithArgs.AsStdFunction(), interval,firstArgument, secondArgument);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
