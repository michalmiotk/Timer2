#include <iostream>

#include <ncurses.h>

#include "SimpleTimer.hpp"

int main()
{  
  std::string userInput;
  std::cout<<"please give time interval in seconds and press ENTER"<<std::endl;
  std::cin>>userInput;
  auto timeInSeconds = std::stoi(userInput); 
  SimpleTimer t{TimerType::oneShot, timeInSeconds*1000, []{std::cout<<"I am one shot"<<std::endl;}};
  t.start();
  t.setTime(10000);
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
