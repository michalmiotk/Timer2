#include <iostream>

#include <ncurses.h>
 
#include "OneShotRunner.hpp"
#include "Stoper.hpp"
#include "types.hpp"
#include "Timer.hpp"

int main()
{  
  std::string userInput;
  std::cout<<"please give time interval in seconds and press ENTER"<<std::endl;
  std::cin>>userInput;
  auto timeInSeconds = std::stoi(userInput); 
  Timer t{TimerType::oneShot, timeInSeconds*1000};
  t.start();
  initscr();
  timeout(-1);  
  char c = '_';
  while (c != 'Q')
  {
    c = getch();
    if (c == 'E')
    {
      printf("%f s\n\r", t.getElapsedTime());
    }
  }
  endwin();
 
  return 0;
}
