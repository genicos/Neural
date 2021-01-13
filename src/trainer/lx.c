#include "lx.h"

void lx_delete(lx *x){
  if(x){
    if(x->examples_responsibility){
      for(uint64_t i = 0; i < x->examples_count*(x->inputs_count+1); i++){
        tensor_delete(x->examples[i]);
      }
    }
    free(x->examples);
  }
  free(x);
}

lx *lx_create(uint32_t examples_count, uint32_t inputs_count, tensor **examples){
  if(!(examples_count * inputs_count) || !examples)
    return NULL;
  
  lx *x = (lx *)malloc(sizeof(lx));
  if(!x)
    return NULL;

  x->examples_count = examples_count;
  x->inputs_count = inputs_count;
  x->examples = examples;
  x->examples_responsibility = false;
 
  return x;
}



tensor *lx_example_input(lx *x, uint32_t example, uint32_t input){
  if(!x){
    return NULL;
  }
  
  return x->examples[example*(x->inputs_count+1) + input];
}

tensor *lx_example_output(lx *x, uint32_t example){
  if(!x){
    return NULL;
  }
  
  return x->examples[example*(x->inputs_count+1) + x->inputs_count];
}
