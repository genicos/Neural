#include "tensor.h"
#include <stdlib.h>

tensor *tensor_create(FORM_ELEMENT *form, FORM_LENGTH_STORE form_length){
  if(!form || !form_length){
    return NULL;
  }


}





tensor* tensor_add(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form, A->form_length);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i] + B->data[i];
  
  return C;
}


tensor* tensor_add_d_1(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form, A->form_length);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = 1;
  
  return C;
}


tensor* tensor_add_d_2(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form, A->form_length);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = 1;
  
  return C;
}


tensor* tensor_sub(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form, A->form_length);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C = A->data[i] - B->data[i];
  
  return C;
}

tensor* tensor_sub_d_1(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form, A->form_length);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = 1;
  
  return C;
}

tensor* tensor_sub_d_2(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form, A->form_length);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = -1;
  
  return C;
}


tensor* tensor_scale(tensor *A, ELEMENT B){
  tensor* C = create_tensor(A->form, A->form_length);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i] * B;
  
  return C;
}

tensor* tensor_scale_d_1(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form, A->form_length);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = B;
  
  return C;
}

tensor* tensor_scale_d_2(tensor *A, tensor *B){
  tensor* C = create_tensor(A->form, A->form_length);
  
  for(DATA_LENGTH_STORE i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i];
  
  return C;
}



tensor* tensor_full(tensor *A, tensor *B){
  tensor* C = create_tensor(&B->form[1], B->form_length-1);
  
  for(DATA_LENGTH_STORE i = 0; i < C->data_length; i++){
    for(DATA_LENGTH_STORE h = 0; h < A->data_length; h++){
      C->data[i] += A->data[h] * B->data[h + (i * A->data_length)];
    }
  }

  return C;
}

tensor* tensor_full_d_1(tensor *A, tensor *B){
  tensor* C = create_tensor(&B->form[1], B->form_length-1);
   
  for(DATA_LENGTH_STORE i = 0; i < C->data_length; i++){
    for(DATA_LENGTH_STORE h = 0; h < A->data_length; h++){
      C->data[i] += B->data[h + (i * A->data_length)];
    }
  }

  return C;
}

tensor* tensor_full_d_1(tensor *A, tensor *B){
  tensor* C = create_tensor(&B->form[1], B->form_length-1);
  
  for(DATA_LENGTH_STORE i = 0; i < C->data_length; i++){
    for(DATA_LENGTH_STORE h = 0; h < A->data_length; h++){
      C->data[i] += A->data[h];
    }
  }

  return C;
}
