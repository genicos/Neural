#include "foam.h"
#include <stdlib.h>



TNSR fish_tnsr(uint8_t *stream, uint32_t *head){
  TNSR ans = 0;
  
  for(uint8_t b = 0; b < sizeof(TNSR); b++){
    ans += stream[*head+b] << (b * 8);
  }
  *head+=sizeof(TNSR);
  
  return ans;
}

void tnode_delete(TNode *t){
  if(t){
    tensor_delete(t->tensor);
    free(t->cause);
    free(t->effect);
    free(t);
  }
}

void foam_delete(Foam *f){
  if(f){
    if(f->tensor_foam){
      for(TNSR i = 0; i< f->length; i++){
        tnode_delete(f->tensor_foam[i]);
      }
      free(f->tensor_foam);
    }
    free(f->inputs);
    free(f->outputs);
    free(f->params);
    free(f);
  }
}

// Reads blueprint from a memory stream
// the /J symbol means a value is 'fished' from the stream, looks like
//
// /J <meaning of value> , <number of bytes fished>
//
Foam *read_blueprint(uint8_t *stream){
  Foam *fresh = (Foam *)calloc(1,sizeof(Foam));
  if(!fresh){
    return NULL;
  }
  
  //little endian
  
  uint32_t head = 0;
  
  
  
  //filling Tnode array
  fresh->length = fish_tnsr(stream, &head);             // /J number of tensors, sizeof(TNSR)
  
  fresh->tensor_foam = (TNode **)calloc(fresh->length, sizeof(TNode *));
  if(!fresh->tensor_foam){
    foam_delete(fresh);
    return NULL;
  }
  for(TNSR i = 0; i < fresh->length; i++){
    TNode *fresh_t = (TNode *)calloc(1,sizeof(TNode));
    if(!fresh_t){
      foam_delete(fresh);
      return NULL;
    }
    
    fresh->tensor_foam[i] = fresh_t;
  }
  
  
  
  //filling input array
  fresh->input_length = fish_tnsr(stream, &head);       // /J number of inputs, sizeof(TNSR) 
  
  fresh->inputs = (TNSR *)calloc(fresh->input_length, sizeof(TNSR));
  if(!fresh->inputs){
    foam_delete(fresh);
    return NULL;
  }
  for(TNSR i = 0; i < fresh->input_length; i++){
    fresh->inputs[i] = fish_tnsr(stream, &head);        // /J input tensor codes, sizeof(TNSR) * input_length
  }
  
  
  //filling output array
  fresh->output_length = fish_tnsr(stream, &head);      // /J number of output tensors, sizeof(TNSR)
  
  fresh->outputs = (TNSR *)calloc(fresh->output_length, sizeof(TNSR));
  if(!fresh->outputs){
    foam_delete(fresh);
    return NULL;
  }
  for(TNSR i = 0; i < fresh->output_length; i++){
    fresh->outputs[i] = fish_tnsr(stream, &head);       // /J output tensor codes, sizeof(TNSR) * output_length
  }
  
  
  //filling parameter array
  fresh->param_length = fish_tnsr(stream, &head);       // /J number of parameter tensors, sizeof(TNSR)
  
  fresh->params = (TNSR *)calloc(fresh->param_length, sizeof(TNSR));
  if(!fresh->params){
    foam_delete(fresh);
    return NULL;
  }
  for(TNSR i = 0; i < fresh->param_length; i++){
    fresh->params[i] = fish_tnsr(stream, &head);        // /J parameter tensor codes, sizeof(TNSR) * param_length
  }
  
  
  
  
  TNSR function_count = fish_tnsr(stream, &head);
  
  //every function has 1 result, and at least 1 operand
  
  //filling tensor_foam with function data
  for(TNSR i = 0; i < function_count; i++){
    uint8_t function = stream[head++];                  // /J function code, 1
    
    
    TNSR result_code = fish_tnsr(stream, &head);        // /J result tensor code, sizeof(TNSR)
    
    fresh->tensor_foam[result_code]->function = function;
    
    fresh->tensor_foam[result_code]->cause = (TNSR *)calloc(f_players[function]-1, sizeof(TNSR));
    if(!fresh->tensor_foam[result_code]->cause){
      foam_delete(fresh);
      return NULL;
    }
    
    fresh->tensor_foam[result_code]->cause_length = f_players[function]-1;
    
    for(uint8_t o = 0; o < f_players[function]-1 ; o++){
      
      TNSR operand_code = fish_tnsr(stream, &head);     // /J operand tensor code
      fresh->tensor_foam[result_code]->cause[o] = operand_code;
      
      
      TNode *operand = fresh->tensor_foam[operand_code];
      
      operand->effect_length++;
      operand->effect = (TNSR *)realloc(operand->effect,
      					operand->effect_length * sizeof(TNSR));
      if(!operand->effect){
        foam_delete(fresh);
        return NULL;
      }
      operand->effect[operand->effect_length - 1] = result_code;
    }
  
  }
  
  return fresh;
}
