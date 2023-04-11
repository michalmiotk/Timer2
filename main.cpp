#include <iostream>

#include <ncurses.h>

#include "SimpleTimer.hpp"
#include "OneShotRunner.hpp"
#include "RecurrentRunner.hpp"
#include "Stoper.hpp"
#include "types.hpp"


int main()
{  
  std::string userInput;
  std::cout<<"please give time interval in seconds and press ENTER"<<std::endl;
  std::cin>>userInput;
  auto timeInSeconds = std::stoi(userInput); 
  SimpleTimer oneShotTimer{std::chrono::seconds{3*timeInSeconds}, [](){ std::cout<<"Hello, I'm a single shot\n\r"; }, std::make_unique<OneShotRunner<>>(), std::make_unique<Stoper>()};
  SimpleTimer recurrentTimer{std::chrono::seconds{timeInSeconds}, [](){ std::cout<<"Running...\n\r"; }, std::make_unique<RecurrentRunner<>>(), std::make_unique<Stoper>()};
  SimpleTimer recurrentTimer150{std::chrono::seconds{int(1.5*timeInSeconds)}, [](){ std::cout<<"Walking...\n\r"; }, std::make_unique<RecurrentRunner<>>(), std::make_unique<Stoper>()};
  oneShotTimer.start( );
  recurrentTimer.start( );
  recurrentTimer150.start();
  initscr();
  timeout(-1);  
  char c = '_';
  while (c != 'Q')
  {
    c = getch();
    if (c == 'E')
    {
      printf("%f s\n\r", oneShotTimer.getElapsedTime().count());
    }
  }
  endwin();
  oneShotTimer.stop();
  recurrentTimer.stop();
  recurrentTimer150.stop();
  return 0;
}
