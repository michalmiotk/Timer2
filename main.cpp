#include <iostream>
#include <thread>
#include "Timer.hpp"
#include "OneShotRunner.hpp"
#include "RecurrentRunner.hpp"

int main()
{
  OneShotRunner oneShotRunner{};
  RecurrentRunner recurrentRunner{};
  Timer t{oneShotRunner};
  
  t.start([](){std::cout<<"a"<<std::endl;}, secondsDouble{1.1});
  for(int i=0;i<3;i++)
  std::cout<<t.getElapsedTime().count()<<std::endl;
  //
  std::this_thread::sleep_for(std::chrono::seconds{3});
  t.stop();
  return 0;
}
