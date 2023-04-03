#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Timer.hpp"
#include "OneShotRunner.hpp"
#include "RecurrentRunner.hpp"
#include "IStoper.hpp"
#include "types.hpp"

using namespace testing;

template <typename T=secondsDouble>
class MockStoper: public IStoper<T>{
public:
    MOCK_METHOD(T, getElapsedTime, (), (const, override));
    MOCK_METHOD(void, start, (), (override));
};

class TestTimer : public ::testing::Test
{
protected:
    MockFunction<void(void)> mockCallback;
    const std::chrono::milliseconds interval{1};
    const int factorWait{10};
    std::unique_ptr<NiceMock<MockStoper<>>> niceMockStoperPtr = std::make_unique<NiceMock<MockStoper<>>>();
    std::unique_ptr<StrictMock<MockStoper<>>> strictMockStoperPtr = std::make_unique<StrictMock<MockStoper<>>>();
};

TEST_F(TestTimer, givenTimerWithOneShotRunner_whenStartIsCalled_thenExpectCallCallback)
{
    EXPECT_CALL(mockCallback, Call());

    Timer<> oneShotTimer{std::make_unique<OneShotRunner<>>(), std::move(niceMockStoperPtr)};
    
    oneShotTimer.start(mockCallback.AsStdFunction(), interval);
    std::this_thread::sleep_for(interval*factorWait);    
}

TEST_F(TestTimer, givenTimerWithRecurrentRunner_whenStartIsCalled_thenExpectCallCallbackAtLeastTwoTimes)
{
    const int timesToBeCalled = 2;
    EXPECT_CALL(mockCallback, Call()).Times(AtLeast(2));

    Timer<> recurrentTimer{std::make_unique<RecurrentRunner<>>(), std::move(niceMockStoperPtr)};
    
    recurrentTimer.start(mockCallback.AsStdFunction(), interval);
    std::this_thread::sleep_for(interval*factorWait*timesToBeCalled);
    recurrentTimer.stop();
    std::cout<<"qoni"<<std::endl;
}
/*
TEST_F(TestTimer, givenOneShotTimer_whenSomeTimePassedFromCallingstart_thenExpectGetElapsedTimeReturnTime)
{
    Timer<> oneShotTimer{std::make_unique<OneShotRunner<>>(), std::make_unique<Stoper<>>()};
    
    oneShotTimer.start([](){}, interval);
    std::this_thread::sleep_for(interval*factorWait);    
    
    const auto getElapsedTimeCallResult = oneShotTimer.getElapsedTime();

    const auto minimumExpectedWait = interval;
    const auto maximumExpectedWait = 2 * interval*factorWait;
    ASSERT_GE(getElapsedTimeCallResult, minimumExpectedWait);
    ASSERT_LE(getElapsedTimeCallResult, maximumExpectedWait);
}
*/

TEST_F(TestTimer, givenTimer_whenCallingstart_thenExpectStoperstartMethodBeCalled)
{
    EXPECT_CALL(*strictMockStoperPtr, start());
    Timer<> timer{std::make_unique<OneShotRunner<>>(), std::move(strictMockStoperPtr)};
    
    timer.start([](){}, interval);
    timer.stop();
}


TEST_F(TestTimer, givenNotStartedTimer_whengetElapsedTimeIsCalled_thenExpectReturnZeroMs)
{
    std::chrono::milliseconds expectedResultOfGetElapsedTime{};
    Timer<> timer{std::make_unique<OneShotRunner<>>(), std::make_unique<Stoper<>>()};
    std::this_thread::sleep_for(interval*factorWait);

    const auto resultOfGetElapsedTime = timer.getElapsedTime();

    EXPECT_EQ(resultOfGetElapsedTime, expectedResultOfGetElapsedTime);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}