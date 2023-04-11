#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SimpleTimer.hpp"
#include "OneShotRunner.hpp"
#include "RecurrentRunner.hpp"
#include "IStoper.hpp"
#include "types.hpp"

using namespace testing;


class MockStoper: public IStoper{
public:
    MOCK_METHOD(secondsDouble, getElapsedTime, (), (const, override));
    MOCK_METHOD(void, start, (), (override));
};

class TestTimer : public ::testing::Test
{
protected:
    MockFunction<void(void)> mockCallback;
    const std::chrono::milliseconds interval{1};
    std::unique_ptr<NiceMock<MockStoper>> niceMockStoperPtr = std::make_unique<NiceMock<MockStoper>>();
    std::unique_ptr<StrictMock<MockStoper>> strictMockStoperPtr = std::make_unique<StrictMock<MockStoper>>();
};

TEST_F(TestTimer, givenTimerWithOneShotRunner_whenStartIsCalled_thenExpectCallCallback)
{
    EXPECT_CALL(mockCallback, Call());

    SimpleTimer oneShotTimer{interval, mockCallback.AsStdFunction(), std::make_unique<OneShotRunner<>>(), std::move(niceMockStoperPtr)};
    
    oneShotTimer.start();
}



TEST_F(TestTimer, givenOneShotTimer_whenTimerFires_thenExpectGetElapsedTimeReturnAtLeastInterval)
{
    SimpleTimer oneShotTimer{interval, mockCallback.AsStdFunction(), std::make_unique<OneShotRunner<>>(), std::make_unique<Stoper>()};
    EXPECT_CALL(mockCallback, Call()).WillOnce(
        Invoke([this, &oneShotTimer]{
            ASSERT_GE(oneShotTimer.getElapsedTime(), this->interval)
            ;}));
    oneShotTimer.start();
}


TEST_F(TestTimer, givenTimer_whenCallingstart_thenExpectStoperstartMethodBeCalled)
{
    EXPECT_CALL(*strictMockStoperPtr, start());
    SimpleTimer timer{interval, []{}, std::make_unique<OneShotRunner<>>(), std::move(strictMockStoperPtr)};
    
    timer.start();
    timer.stop();
}


TEST_F(TestTimer, givenNotStartedTimer_whengetElapsedTimeIsCalledAfterAtLeast10ms_thenExpectReturnZeroMs)
{
    constexpr std::chrono::milliseconds timeToWait{10};
    constexpr std::chrono::milliseconds expectedResult{};
    SimpleTimer timer{std::chrono::milliseconds{0}, []{}, std::make_unique<OneShotRunner<>>(), std::make_unique<Stoper>()};
    std::this_thread::sleep_for(timeToWait);

    const auto resultOfGetElapsedTime = timer.getElapsedTime();

    EXPECT_EQ(resultOfGetElapsedTime, expectedResult);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}