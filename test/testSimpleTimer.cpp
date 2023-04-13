#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SimpleTimer.hpp"

using namespace testing;


class TestTimer : public ::testing::Test
{
protected:
    MockFunction<void(void)> mockCallback;
    const milliseconds interval{1};
};

TEST_F(TestTimer, givenOneShotTimer_whenStartIsCalled_thenExpectCallCallback)
{
    const milliseconds timeToWait{1};
    EXPECT_CALL(mockCallback, Call());

    SimpleTimer oneShotTimer{TimerType::oneShot, timeToWait, mockCallback.AsStdFunction()};
    
    oneShotTimer.start();
}



TEST_F(TestTimer, givenOneShotTimer_whenTimerFires_thenExpectGetElapsedTimeReturnValueGreaterThanZero)
{
    SimpleTimer oneShotTimer{TimerType::oneShot, interval, mockCallback.AsStdFunction()};
    EXPECT_CALL(mockCallback, Call()).WillOnce(
        Invoke([this, &oneShotTimer]{
            ASSERT_GT(oneShotTimer.getElapsedTime(), 0.0f)
            ;}));
    oneShotTimer.start();
}

TEST_F(TestTimer, givenNotStartedOneShotTimer_whengetElapsedTimeIsCalledAfterAtLeast10ms_thenExpectReturnZeroMs)
{
    constexpr std::chrono::milliseconds timeToWait{10};
    constexpr secondsDouble expectedResult{};
    SimpleTimer oneShotTimer{TimerType::oneShot, interval, mockCallback.AsStdFunction()};
    std::this_thread::sleep_for(timeToWait);

    const auto resultOfGetElapsedTime =  oneShotTimer.getElapsedTime();

    EXPECT_EQ(resultOfGetElapsedTime, expectedResult);
}


TEST_F(TestTimer, givenStartedAndStoppedOneShotTimer_WhenAnotherStartIsCalled_thenExpectMethodBeCalled)
{
    constexpr milliseconds initialTimeToWait{100000};
    constexpr milliseconds timeToWaitAfterStop{1};
    EXPECT_CALL(mockCallback, Call());
    SimpleTimer oneShotTimer{TimerType::oneShot, initialTimeToWait, mockCallback.AsStdFunction()};
    oneShotTimer.start();
    oneShotTimer.stop();

    oneShotTimer.setTime(timeToWaitAfterStop);
    oneShotTimer.start();
}

TEST_F(TestTimer, givenOneShotSimpleTimer_whenStartIsCalledWithMinus1MillisecondsTimeToCall_thenExpectThrow)
{
    constexpr milliseconds timeToWait{-1};
    SimpleTimer oneShotTimer{TimerType::oneShot, timeToWait, mockCallback.AsStdFunction()};
    EXPECT_THROW({
        oneShotTimer.start();
    }, IntervalLessThanZero);    
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
