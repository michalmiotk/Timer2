#include <iostream>
#include <thread>


#include <termios.h>
#include <ncurses.h>

#include "Timer.hpp"
#include "OneShotRunner.hpp"
#include "RecurrentRunner.hpp"
#include "Stoper.hpp"
#include "types.hpp"
#include "IStoper.hpp"

int main()
{
  Timer<secondsDouble> oneShotTimer{std::make_unique<OneShotRunner<secondsDouble>>(), std::make_unique<Stoper<secondsDouble>>()};
  Timer<secondsDouble> recurrentTimer{std::make_unique<RecurrentRunner<secondsDouble>>(), std::make_unique<Stoper<secondsDouble>>()};

  oneShotTimer.start([](){ printf("oneShotTimer\n\r"); }, secondsDouble{2});
  recurrentTimer.start([](){ printf("recurrentTimer\n\r"); }, secondsDouble{1});
  
  initscr();
  timeout(-1);  
  char c = '_';
  while (c != 'e')
  {
    c = getch();
    if (c == 'p')
    {
      printf("%f s\n\r", oneShotTimer.getElapsedTime().count());
    }
  }
  endwin();
  oneShotTimer.stop();
  recurrentTimer.stop();
  return 0;
}
