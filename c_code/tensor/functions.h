#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdbool.h>
#include ".h"

typedef struct tensor_function{

  tensor *(*f)     (tensor *, tensor *, tensor *);
  tensor *(*f_d_1) (tensor *, tensor *, tensor *);
  tensor *(*f_d_2) (tensor *, tensor *, tensor *);

  tensor *(*create)          (tensor *, tensor *);

  bool pairwise_to_first;
  bool pairwise_to_second;

} tensor_function;

tensor *tensor_cartesian_product(tensor *A, tensor *B);





tensor *tensor_add    (tensor *C, tensor *A, tensor *B);
tensor *tensor_add_d_1(tensor *C, tensor *A, tensor *B);
tensor *tensor_add_d_2(tensor *C, tensor *A, tensor *B);

tensor *tensor_add_create        (tensor *A, tensor *B);

const tensor_function add = {
  
  .f     = &tensor_add,
  .f_d_1 = &tensor_add_d_1,
  .f_d_2 = &tensor_add_d_2,
  
  .create = &tensor_add_create,
  
  .pairwise_to_first = true,
  .pairwise_to_second = true,
};




tensor *tensor_sub    (tensor *C, tensor *A, tensor *B);
tensor *tensor_sub_d_1(tensor *C, tensor *A, tensor *B);
tensor *tensor_sub_d_2(tensor *C, tensor *A, tensor *B);

tensor *tensor_sub_create        (tensor *A, tensor *B);

const tensor_function sub = {
  
  .f     = &tensor_sub,
  .f_d_1 = &tensor_sub_d_1,
  .f_d_2 = &tensor_sub_d_2,
  
  .create = &tensor_sub_create,
  
  .pairwise_to_first = true,
  .pairwise_to_second = true,
};




tensor *tensor_scale    (tensor *C, tensor *A, tensor *B);
tensor *tensor_scale_d_1(tensor *C, tensor *A, tensor *B);
tensor *tensor_scale_d_2(tensor *C, tensor *A, tensor *B);

tensor *tensor_scale_create        (tensor *A, tensor *B);

const tensor_function scale = {
  
  .f     = &tensor_scale,
  .f_d_1 = &tensor_scale_d_1,
  .f_d_2 = &tensor_scale_d_2,
  
  .create = &tensor_scale_create,
  
  .pairwise_to_first = true,
  .pairwise_to_second = true,
};




tensor *tensor_full    (tensor *C, tensor *A, tensor *B);
tensor *tensor_full_d_1(tensor *C, tensor *A, tensor *B);
tensor *tensor_full_d_2(tensor *C, tensor *A, tensor *B);

tensor *tensor_full_create        (tensor *A, tensor *B);

const tensor_function full = {
  
  .f     = &tensor_full,
  .f_d_1 = &tensor_full_d_1,
  .f_d_2 = &tensor_full_d_2,
  
  .create = &tensor_full_create,

  .pairwise_to_first  = true,
  .pairwise_to_second = true,
};




const tensor_function *tensor_function_table[] = {
  &add,
  &sub, 
  &scale, 
  &full,
};


#endif
