#include "tensor.h"


tensor* tensor_add(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i] + B->data[i];
  
  return C;
}


tensor* tensor_add_d_1(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = 1;
  
  return C;
}


tensor* tensor_add_d_2(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = 1;
  
  return C;
}


tensor* tensor_sub(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C = A->data[i] - B->data[i];
  
  return C;
}

tensor* tensor_sub_d_1(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = 1;
  
  return C;
}

tensor* tensor_sub_d_2(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = -1;
  
  return C;
}


tensor* tensor_scale(tensor *A, ELEMENT B){
  tensor* C = create_tensor(A->form);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i] * B;
  
  return C;
}

tensor* tensor_scale_d_1(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = B;
  
  return C;
}

tensor* tensor_scale_d_2(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i];
  
  return C;
}

