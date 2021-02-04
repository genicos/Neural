#include <curses.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>

#include "../network/network.h"
#include "../trainer/lx.h"


void pin_str(int row, int col, const char *str){
  mvaddstr(row, col - strlen(str)/2, str);
}


void draw_options(int row, int col, int hei, int count, int choice, const char **options){
  
  unsigned long width = 0;
  
  for(int i = 0; i < count; i++){
    if(width < strlen(options[i])){
      width = strlen(options[i]);
    }
  }
  
  width += 4;
  
  if(hei-row > count*4){
    
    for(int i = 0; i < count; i++){
      if(i == choice){
        mvaddch(row + 2*i, col - width/2,     ACS_RTEE);
        mvaddch(row + 2*i, col - width/2 + 2, ACS_LTEE);
      }
      mvaddch(row + 2*i, col - width/2 + 1, ACS_DIAMOND);
      mvaddstr(row + 2*i, col - width/2 + 4, options[i]);
    }
  }
  
  
  
  
}

int main(){
  
  printf("Demo\n");
  
  lx *mnist = lx_read("src/demo/mnist.lx");
  if(!mnist){
    printf("Failed\n"); //I need to create mnist.lx
  }
  
  // initialize ncurses //
  initscr();
  cbreak();
  noecho();
  
  clear();
  //
  
  bool running = true;
  
  int wid = 0, hei = 0;
  getmaxyx(stdscr, hei, wid);
  printf("%d, %d\n", wid, hei);
 
  pin_str(hei/2-5,wid/2,"Neural Network training ground");
  pin_str(hei/2-4,wid/2,"Created by Nicolas Ayala");
  
 /* 
  pin_str(hei/2  ,wid/2,"|A| Create network");
  
  pin_str(hei/2+2,wid/2,"|B| Open network  ");
 
  
   
  int option_column = -8;
  
  mvaddch(hei/2-1,wid/2 + option_column-1,ACS_ULCORNER); 
  mvaddch(hei/2-1,wid/2 + option_column+1,ACS_URCORNER); 
  mvaddch(hei/2+1,wid/2 + option_column-1,ACS_LLCORNER); 
  mvaddch(hei/2+1,wid/2 + option_column+1,ACS_LRCORNER); 
  
  
  mvaddch(hei/2,wid/2 + option_column-1,ACS_RTEE); 
  mvaddch(hei/2,wid/2 + option_column+1,ACS_LTEE); 
  
  mvaddch(hei/2-1,wid/2 + option_column,ACS_HLINE);
  mvaddch(hei/2+1,wid/2 + option_column,ACS_HLINE); 
  
  while(running){
    break;
  }
  */

  const char *main_menu_options[2] = {"Open network", "Create network"};  
  draw_options(hei/2, wid/2, hei, 2, 0, main_menu_options);
  
  getch();
  endwin();
  
  lx_delete(mnist);
   
  return 0;
}
