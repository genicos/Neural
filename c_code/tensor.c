#include "tensor.h"

//Requires A and B to have equal FORMs
tensor* tensor_add(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C = A->data[i] + B->data[i];
  
  return C;
}


//Requires A and B to have equal FORMs
tensor* tensor_sub(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C = A->data[i] - B->data[i];
  
  return C;
}


tensor* tensor_scale(tensor *A, ELEMENT c){
  tensor* B = create_tensor(A->form);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    B = A->data[i] * c;
  
  return B;
}

