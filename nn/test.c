#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "foam.h"

int main(){
  uint8_t data[] = 
  {13,0,
    3,0, 1,0, 2,0, 9,0,
    1,0,12,0,
    3,0, 0,0, 3,0, 7,0,
    7,0,
    0,   4,0, 1,0, 0,0,
    1,   6,0, 4,0,
    2,   5,0, 2,0, 3,0,
    3,   8,0, 5,0,
    4,  10,0, 6,0, 7,0,
    5,  12,0,10,0,11,0,
    6,  11,0, 8,0, 9,0};
  Foam *in_delta = read_blueprint(data);
  if(in_delta){
    printf("We bloody did it mate\n");
  }
  printf("\nIn Delta");
  printf("\nlength %d",in_delta->length);
  printf("\ninput_length %d", in_delta->input_length);
  printf("\ninputs");
  for(int h = 0; h < in_delta->input_length; h++){
    printf(" %d,", in_delta->inputs[h]);
  }
  printf("\noutput_length %d", in_delta->output_length);
  printf("\noutputs");
  for(int h = 0; h < in_delta->output_length; h++){
    printf(" %d,", in_delta->outputs[h]);
  }
  printf("\nparam_length %d", in_delta->param_length);
  printf("\nparams");
  for(int h = 0; h < in_delta->param_length; h++){
    printf(" %d,", in_delta->params[h]);
  }
  printf("\ntensor_foam");
  for(int h = 0; h < in_delta->length; h++){
    printf("\n [%d]", h);
    TNode *heres = in_delta->tensor_foam[h];
    
    printf("\n  function %d", heres->function);

    printf("\n  cause_length %d", heres->cause_length);
    printf("\n  cause");
    for(int i = 0; i < heres->cause_length; i++){
      printf(" %d,", heres->cause[i]);
    }

    printf("\n  effect_length %d", heres->effect_length);
    printf("\n  effect");
    for(int i = 0; i < heres->effect_length; i++){
      printf(" %d,", heres->effect[i]);
    }
  }
  printf("\n\n"); 
  
  foam_delete(in_delta);
  
  
  uint8_t newdata[] = {
  13,0,
   1,0, 0,0,
   7,0, 6,0, 7,0, 8,0, 9,0,10,0,11,0,12,0,
   5,0, 1,0, 2,0, 3,0, 4,0, 5,0,
   7,0,
   0,   6,0, 0,0, 1,0,
   1,   7,0, 0,0,
   2,   8,0, 0,0, 2,0,
   3,   9,0, 0,0,
   4,  10,0, 0,0, 3,0,
   5,  11,0, 0,0, 4,0,
   6,  12,0, 0,0, 5,0,
  };
  in_delta = read_blueprint(newdata);
  
  if(in_delta){
    printf("We bloody did it mate\n");
  }
  printf("\nOut Delta");
  printf("\nlength %d",in_delta->length);
  printf("\ninput_length %d", in_delta->input_length);
  printf("\ninputs");
  for(int h = 0; h < in_delta->input_length; h++){
    printf(" %d,", in_delta->inputs[h]);
  }
  printf("\noutput_length %d", in_delta->output_length);
  printf("\noutputs");
  for(int h = 0; h < in_delta->output_length; h++){
    printf(" %d,", in_delta->outputs[h]);
  }
  printf("\nparam_length %d", in_delta->param_length);
  printf("\nparams");
  for(int h = 0; h < in_delta->param_length; h++){
    printf(" %d,", in_delta->params[h]);
  }
  printf("\ntensor_foam");
  for(int h = 0; h < in_delta->length; h++){
    printf("\n [%d]", h);
    TNode *heres = in_delta->tensor_foam[h];
    
    printf("\n  function %d", heres->function);

    printf("\n  cause_length %d", heres->cause_length);
    printf("\n  cause");
    for(int i = 0; i < heres->cause_length; i++){
      printf(" %d,", heres->cause[i]);
    }

    printf("\n  effect_length %d", heres->effect_length);
    printf("\n  effect");
    for(int i = 0; i < heres->effect_length; i++){
      printf(" %d,", heres->effect[i]);
    }
  }
  foam_delete(in_delta);


}
