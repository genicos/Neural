#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdbool.h>
#include "tensor.h"

typedef struct tensor_function{

  tensor *(*f)     (tensor *, tensor *, tensor *);
  tensor *(*f_d_1) (tensor *, tensor *, tensor *);
  tensor *(*f_d_2) (tensor *, tensor *, tensor *);

  tensor *(*create)          (tensor *, tensor *);

  bool pairwise_to_first;
  bool pairwise_to_second;

} tensor_function;

tensor *tensor_cartesian_product(tensor *A, tensor *B);

tensor *tensor_chain_rule(tensor *AB, tensor *BC);

#define FUNCTION_CT 4

extern const tensor_function *tensor_function_table[FUNCTION_CT];




tensor *tensor_add    (tensor *C, tensor *A, tensor *B);
tensor *tensor_add_d_1(tensor *C, tensor *A, tensor *B);
tensor *tensor_add_d_2(tensor *C, tensor *A, tensor *B);

tensor *tensor_add_create        (tensor *A, tensor *B);






tensor *tensor_sub    (tensor *C, tensor *A, tensor *B);
tensor *tensor_sub_d_1(tensor *C, tensor *A, tensor *B);
tensor *tensor_sub_d_2(tensor *C, tensor *A, tensor *B);

tensor *tensor_sub_create        (tensor *A, tensor *B);






tensor *tensor_scale    (tensor *C, tensor *A, tensor *B);
tensor *tensor_scale_d_1(tensor *C, tensor *A, tensor *B);
tensor *tensor_scale_d_2(tensor *C, tensor *A, tensor *B);

tensor *tensor_scale_create        (tensor *A, tensor *B);






tensor *tensor_full    (tensor *C, tensor *A, tensor *B);
tensor *tensor_full_d_1(tensor *C, tensor *A, tensor *B);
tensor *tensor_full_d_2(tensor *C, tensor *A, tensor *B);

tensor *tensor_full_create        (tensor *A, tensor *B);






#endif
