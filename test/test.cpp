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
    int actualCalled{};
    const int timesToBeCalled = 2;
    Timer<> recurrentTimer{std::make_unique<RecurrentRunner<>>(), std::move(niceMockStoperPtr)};
    EXPECT_CALL(mockCallback, Call()).Times(AtLeast(timesToBeCalled)).WillRepeatedly(Invoke([&actualCalled, &recurrentTimer](){
        if(actualCalled < timesToBeCalled){
            actualCalled++;
        }else{
            recurrentTimer.stop();
        }
    }));

    recurrentTimer.start(mockCallback.AsStdFunction(), interval);    
}

TEST_F(TestTimer, givenOneShotTimer_whenTimerFires_thenExpectGetElapsedTimeReturnAtLeastInterval)
{
    Timer<> oneShotTimer{std::make_unique<OneShotRunner<>>(), std::make_unique<Stoper<>>()};
    auto functionToStart = [&oneShotTimer, interval=interval](){ASSERT_GE(oneShotTimer.getElapsedTime(), interval);};
    oneShotTimer.start(functionToStart, interval);    
}


TEST_F(TestTimer, givenTimer_whenCallingstart_thenExpectStoperstartMethodBeCalled)
{
    EXPECT_CALL(*strictMockStoperPtr, start());
    Timer<> timer{std::make_unique<OneShotRunner<>>(), std::move(strictMockStoperPtr)};
    
    timer.start([]{}, interval);
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