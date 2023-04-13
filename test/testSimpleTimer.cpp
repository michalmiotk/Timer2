#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SimpleTimer.hpp"

using namespace testing;


class TestTimer : public ::testing::Test
{
protected:
    MockFunction<void(void)> mockCallback;
    bool wait{true};
};

TEST_F(TestTimer, givenOneShotTimer_whenStartIsCalled_thenExpectCallCallback)
{
    const milliseconds timeToWait{1};
    EXPECT_CALL(mockCallback, Call()).WillOnce(Invoke([&wait = this->wait](){wait = false;}));

    SimpleTimer oneShotTimer{TimerType::oneShot, timeToWait, mockCallback.AsStdFunction()};
    
    oneShotTimer.start();
    while(wait)
    {}
}



TEST_F(TestTimer, givenOneShotTimer_whenTimerFires_thenExpectGetElapsedTimeReturnValueGreaterThanZero)
{
    const milliseconds timeToWait{1};
    SimpleTimer oneShotTimer{TimerType::oneShot, timeToWait, mockCallback.AsStdFunction()};
    EXPECT_CALL(mockCallback, Call()).WillOnce(
        Invoke([this, &oneShotTimer, &wait = this->wait]{
                ASSERT_GT(oneShotTimer.getElapsedTime(), 0.0f);
                wait = false;
            }));
    oneShotTimer.start();
    while(wait)
    {}
}

TEST_F(TestTimer, givenNotStartedOneShotTimer_whengetElapsedTimeIsCalledAfterAtLeast10ms_thenExpectReturnZeroMs)
{
    constexpr std::chrono::milliseconds timeToSleep{10};
    constexpr milliseconds timeToWait{10};
    constexpr secondsDouble expectedResult{};
    SimpleTimer oneShotTimer{TimerType::oneShot, timeToWait, mockCallback.AsStdFunction()};
    std::this_thread::sleep_for(timeToSleep);

    const auto resultOfGetElapsedTime =  oneShotTimer.getElapsedTime();

    EXPECT_EQ(resultOfGetElapsedTime, expectedResult);
}


TEST_F(TestTimer, givenStartedAndStoppedOneShotTimer_WhenAnotherStartIsCalled_thenExpectMethodBeCalled)
{
    constexpr milliseconds initialTimeToWait{100'000};
    constexpr milliseconds timeToWaitAfterStop{1};
    
    EXPECT_CALL(mockCallback, Call()).WillOnce(Invoke([&wait = this->wait](){wait = false;}));
    SimpleTimer oneShotTimer{TimerType::oneShot, initialTimeToWait, mockCallback.AsStdFunction()};
    oneShotTimer.start();
    oneShotTimer.stop();

    oneShotTimer.setTime(timeToWaitAfterStop);
    oneShotTimer.start();
    while(wait)
    {}
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
