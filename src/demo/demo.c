#include <curses.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>

#include "../network/network.h"
#include "../lx/lx.h"



void pin_str(int row, int col, const char *str){
  mvaddstr(row, col - strlen(str)/2, str);
}


int main(){
  
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
  
  
  lx *mnist = lx_read("src/demo/mnist.lx");
  if(!mnist){
    //mnist.lx is missing, it must be created with images and label files.
    
    FILE *images = fopen("src/demo/train-images-idx3-ubyte", "r");
    if(!images){
      printf("Failed to find mnist images\n");
      return 1;
    } 
    IO *images_io = io_create(images);
    if(!images_io){
      printf("failed to create io\n");
      printf("FAIL\n");
      return 1;
    }
    
    
    FILE *labels = fopen("src/demo/train-labels-idx1-ubyte", "r");
    if(!labels){
      printf("Failed to find mnist label\n");
      return 2;
    }
    IO *labels_io = io_create(labels);
    if(!labels_io){
      printf("Failed to create labels_io\n");
      printf("FAIL\n");
      return 1;
    }
  
  
  
    int tensors = 120000;
    tensor *ts[120000];// = (tensor **)calloc(tensors, sizeof(tensor *));
    
    FORM_ELEMENT image_form[2] = {28,28};
    FORM_ELEMENT label_form[1] = {10};
    
    fseek(images, 16, SEEK_SET);
    for(int i = 0; i < 60000; i++){ //going through training digits
      tensor *t = tensor_create(2, image_form);
      tensor_create_data(t);
      for(int j = 0; j < 28*28; j++){
        t->data[j] = read_1_byte(images_io);
      }
      ts[i*2] = t;
    }
    
    fseek(labels, 8, SEEK_SET);
    for(int i = 0; i < 60000; i++){ //going through training labels
      tensor *t = tensor_create(1, label_form);
      tensor_create_data(t);
      t->data[read_1_byte(labels_io)] = 1;
      ts[i*2+1] = t;
    }
    
    io_delete(images_io);
    io_delete(labels_io);
    
    mnist = lx_create(60000,1,ts);
    if(!mnist){
      printf("Failed to create lx\n");
      printf("FAIL\n");
      return 1;
    }
    lx_save("src/demo/mnist.lx", mnist);
  }
 


   
  
  network *trainer = network_read("src/demo/MNIST-trainer");
  if(!trainer){
    return 1;
  }
  
   
  
  int sample_size = 400;
  
  
  for(uint32_t i = 0; i < mnist->examples_count; i++){
    if( (((double)rand()) /RAND_MAX) < ((double)sample_size / (mnist->examples_count - i) )) {
      sample_size--;
      
    }
  }
  
  
  
  getch();
  endwin();
  
  lx_delete(mnist);
  
  return 0;
}
