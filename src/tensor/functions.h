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

//must create a tensor with this to calculate partial derivatives
tensor *tensor_cartesian_product(tensor *A, tensor *B);

//Inputs:
// AB: Partial derivative of A with respect to B
// BC: Partial derivative of B with respect to C
//Returns:
// Partial derivative of A with respect to C
tensor *tensor_chain_rule(tensor *AB, tensor *BC);

//Creates all zero tensor
tensor *tensor_zero(FORM_LENGTH form_length, FORM_ELEMENT *form);

//Creates an Identity matrix, 
// a tensor with form {s,s}
// which is filled with 0's
// except for the main diagonal, which is full of 1's
tensor *tensor_identity(FORM_ELEMENT s);

#define FUNCTION_CT 5

extern const tensor_function *tensor_function_table[FUNCTION_CT];



//i should change C A B


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








tensor *tensor_amass    (tensor *C, tensor *A, tensor *B);
tensor *tensor_amass_d_1(tensor *C, tensor *A, tensor *B);
tensor *tensor_amass_d_2(tensor *C, tensor *A, tensor *B);

tensor *tensor_amass_create        (tensor *A, tensor *B);








tensor *tensor_softmax    (tensor *C, tensor *A, tensor *B);
tensor *tensor_softmax_d_1(tensor *C, tensor *A, tensor *B);
tensor *tensor_softmax_d_2(tensor *C, tensor *A, tensor *B);

tensor *tensor_softmax_create        (tensor *A, tensor *B);








#endif
