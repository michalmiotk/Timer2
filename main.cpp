#include <iostream>
#include <thread>
#include "Timer.hpp"

int main()
{
 
  Timer t{};
  t.startRecurrent([](){std::cout<<"a"<<std::endl;}, secondsDouble{1.1});
  for(int i=0;i<3;i++)
  std::cout<<t.getElapsedTime().count()<<std::endl;
  //
  std::this_thread::sleep_for(std::chrono::seconds{3});
  t.stop();
  return 0;
}
