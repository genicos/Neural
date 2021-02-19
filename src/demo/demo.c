#include <curses.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>

#include "../network/network.h"
#include "../lx/lx.h"
#include "../trainer/train.h"


void pin_str(int row, int col, const char *str){
  mvaddstr(row, col - strlen(str)/2, str);
}

void draw_matrix(int row, int col, double scale, tensor *t){
  
  char *degrees = " .:-=+*#%@";
  
  for(DATA_LENGTH r = 0; r < t->form[0]; r++){
    for(DATA_LENGTH c = 0; c < t->form[1]; c++){
      int index = (int)(t->data[r*t->form[0] + c]/scale * strlen(degrees)) ;
      if(index < 0)
        index = 0;
      else if((unsigned long)index >= strlen(degrees))
        index = 0;
      
      mvaddch(row + r,col + c, 
        degrees[index]);
    }
  }
  
}


int main(){
  
  // initialize ncurses //
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, 1);
  
  
  clear();
  //
  
  
  int wid = 0, hei = 0;
  getmaxyx(stdscr, hei, wid);
  printf("%d, %d\n", wid, hei);
 
  //pin_str(hei/2-5,wid/2,"Neural Network training ground");
  //pin_str(hei/2-4,wid/2,"Created by Nicolas Ayala");
  
  
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
  
  
  //draw_matrix(4, 5, 256, lx_example_input(mnist, 0, 0));
   
  
  network *trainer = network_read("src/demo/MNIST-trainer");
  if(!trainer){
    return 1;
  }
  
  NODES_LENGTH parameters[1] = {1};
  network_add_parameters(trainer, 1, parameters);
  
  trainer->inputs_length = 1;
  trainer->truth  = 4; 
   
  bool running = true;
  
  bool training = false;
  double training_sample_size = 400;

  bool see_sample = false;
  int sample = 0;
  
  bool randomize = false;
  
  mvaddstr(2, 0, "A: Quit Demo");
  mvaddstr(4, 0, "T: Train network");
  mvaddstr(6, 0, "E: Test network");
  mvaddstr(8, 0, "S: Sample network");
  mvaddstr(10, 0, "R: Randomize parameters");
  
  mvaddstr(2, 20, "Demo is still in the works");
   
  while(running){ 
    
    
    int c = getch();
    
    if(training){
      
      train(trainer, 0.02, 0.02, (EXAMPLES_COUNT)training_sample_size, mnist);
      
    }
    
    if(see_sample){
      draw_matrix(20, 0, 256, lx_example_input(mnist, sample, 0));
      tensor *output = trainer->nodes[trainer->nodes[trainer->root]->parent_1]->t;
      
      for(int i = 0; i < 10; i++){
        mvaddch(20 + i, 28, '0' + i);
        mvaddch(20 + i, 29, ':');
        
        double output_i = output->data[i];
        mvaddch(20 + i, 30, '0' + (int)output_i);
        mvaddch(20 + i, 31, '.');
        
        for(int j = 0; j < 5; j++){
          output_i *= 10;
          mvaddch(20 + i, 32 + j, '0' + ((int)output_i)%10);
        }
        
      }
    }
    
    
    
    if(c == 'a'){
      running = false;
    }
    
    
    
    if(c == 's'){
      sample = rand()%60000;
      trainer->nodes[0]->t = lx_example_input(mnist, sample, 0);
      trainer->nodes[4]->t = lx_example_output(mnist, sample);
      network_clean(trainer);
      node_solve(trainer, trainer->root);
      see_sample = true;
      
      
    }
    
    if(c == 'r'){
      
      randomize_parameters(trainer, 0, 0.02);
    }
    
    if(c == 't'){
      training = !training;
    }
     
  }
  
  
  endwin();
   
  network_print(trainer, "f");
  
  lx_delete(mnist);
  network_delete(trainer);
  return 0;
}
