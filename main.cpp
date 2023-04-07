#include <iostream>

#include <ncurses.h>

#include "Timer.hpp"
#include "OneShotRunner.hpp"
#include "RecurrentRunner.hpp"
#include "Stoper.hpp"
#include "types.hpp"


int main()
{
  Timer oneShotTimer{std::make_unique<OneShotRunner<>>(), std::make_unique<Stoper>()};
  Timer recurrentTimer{std::make_unique<RecurrentRunner<>>(), std::make_unique<Stoper>()};
  Timer recurrentTimer150{std::make_unique<RecurrentRunner<>>(), std::make_unique<Stoper>()};
  
  std::string userInput;
  std::cout<<"please give time interval in seconds and press ENTER"<<std::endl;
  std::cin>>userInput;
  auto timeInSeconds = std::stoi(userInput); 
  oneShotTimer.start([](){ printf("Hello, I'm a single shot\n\r"); }, std::chrono::seconds{3*timeInSeconds});
  recurrentTimer.start([](){ printf("Running...\n\r"); }, std::chrono::seconds{timeInSeconds});
  recurrentTimer150.start([](){ printf("Walking...\n\r"); }, std::chrono::seconds{int(1.5*timeInSeconds)});
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
