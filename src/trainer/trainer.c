#include "../project.h"
#include "../network/pderivative.h"
#include "lx.h"


int main(int argc, char** argv){
  printf("Where is the network?\n");
  
  printf("Where are the examples?\n");
  
  FILE *images = fopen("src/trainer/train-images-idx3-ubyte", "r");
  if(!images){
    printf("WHY\n");
    return 1;
  } 
  
  FILE *labels = fopen("src/trainer/train-labels-idx1-ubyte", "r");
  if(!labels){
    printf("GAH\n");
    return 2;
  }
  
  
  int tensors = 120000;
  tensor **ts = (tensor **)calloc(tensors, sizeof(tensor *));
  
  FORM_ELEMENT image_form[2] = {28,28};
  FORM_ELEMENT label_form[1] = {10};
  
  fseek(images, 16, SEEK_SET);
  for(int i = 0; i < 60000; i++){ //going through training digits
    tensor *t = tensor_create(2, image_form);
    tensor_create_data(t);
    for(int j = 0; j < 28*28; j++){
      t->data[j] = getc(images);
    }
    ts[i*2] = t;
  }

  fseek(labels, 8, SEEK_SET);
  for(int i = 0; i < 60000; i++){ //going through training labels
    tensor *t = tensor_create(1, label_form);
    tensor_create_data(t);
    t->data[getc(labels)] = 1;
    ts[i*2+1] = t;
  }
  tensor_print(ts[0], "f");
  tensor_print(ts[1], "f");
  tensor_print(ts[3], "f");
  tensor_print(ts[5], "f");
  tensor_print(ts[7], "f");
 
  /*                                           //runs very very slow 
  lx *lex = lx_create(60000,1,ts);
  if(!lex){
    printf("FAILED 989\n");
  }
  
  lx_save("LX_TEST_SAVE", lex);
  lx *rec = lx_read("LX_TEST_SAVE");
  
  lx_save("LX_TEST_SAVE2", rec);
    
  lx_delete(lex);
  lx_delete(rec);
  */

  fclose(images);
  fclose(labels);
   
  for(int i = 0; i < 120000; i++){
    tensor_delete(ts[i]);
  }
  free(ts);
  
  return 0; 
}
