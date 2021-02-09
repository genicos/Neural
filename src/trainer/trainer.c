#include "../project.h"
#include "../network/pderivative.h"
#include "../lx/lx.h"


int main(int argc, char** argv){
  
  FILE *images = fopen("src/trainer/train-images-idx3-ubyte", "r");
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
   
  
  FILE *labels = fopen("src/trainer/train-labels-idx1-ubyte", "r");
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
  tensor **ts = (tensor **)calloc(tensors, sizeof(tensor *));
  
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
  
  printf("Sucsessfully read MNIST images and labels\n");
  
  char *display = " .:-=+*#%@";
  
  for(uint32_t k = 0; k < 4; k++){  
    printf("Examples #%d\n", k);
    printf("  Label: 0123456789\n");
    printf("         ");
    for(int l = 0; l < 10; l++){
      putchar((ts[k*2+1]->data[l] > 0.5)?'@':' ');
    }
    printf("\n  Image:\n");
    for(uint32_t i = 0; i < 28; i++){
     
      for(uint32_t j = 0; j < 28; j++){
        putchar(display[(int)(ts[k*2]->data[28*i + j] / 25.6)]);
      }
      putchar('\n');
    }
  }
 
  
  lx *lex = lx_create(60000,1,ts); 
  if(!lex){
    printf("Failed to create lx\n");
    printf("FAIL\n");
    return 1;
  } 
  
  lx_save("LX_TEST_SAVE", lex);
  lx *rec = lx_read("LX_TEST_SAVE");
  
  lx_save("LX_TEST_SAVE2", rec);
    
  lx_delete(lex);
  lx_delete(rec);
  
  io_delete(images_io);
  io_delete(labels_io);

  fclose(images);
  fclose(labels);
  
  printf("lX save and read test passed\n");
  
  for(int i = 0; i < 120000; i++){
    tensor_delete(ts[i]);
  }
  free(ts);
  
  
  
  return 0; 
}
