#ifndef __FOAM_H__
#define __FOAM_H__

#include "tensor.h"

typedef uint16_t TNSR;


typedef struct TNode{
  Tensor *tensor;
  
  uint8_t function;

  TNSR *cause;
  uint8_t cause_length;

  TNSR *effect;
  uint8_t effect_length;
} TNode;

typedef struct Foam{
  TNode **tensor_foam;//all tnodes
  TNSR length;

  TNSR *inputs;//index in tensor_foam 
  TNSR input_length;
  
  TNSR *outputs;
  TNSR output_length;

  TNSR *params;
  TNSR param_length;
} Foam;

void tnode_delete(TNode *t);

void foam_delete(Foam *f);


Foam *read_blueprint(uint8_t *stream);

Foam *read_tensors(uint8_t *stream);


Foam *enter_input(Foam *f, Tensor *input, TNSR in);

Foam *set_param(Foam *f, Tensor *param, TNSR par);

Tensor *calc_output(Foam *f, TNSR out);


#endif
