#include <iostream>
#include <thread>


#include <termios.h>
#include <ncurses.h>

#include "Timer.hpp"
#include "OneShotRunner.hpp"
#include "RecurrentRunner.hpp"


int main()
{

  OneShotRunner oneShotRunner{};
  RecurrentRunner recurrentRunner{};
  Timer oneShotTimer{oneShotRunner};
  Timer recurrentTimer{recurrentRunner};

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
