#include "project.h"
#include "tensor.h"
#include <stdlib.h>

#include <stdio.h>

void tensor_delete_data(tensor *t){
  if(t){
    free(t->data);
  }
}

void tensor_delete(tensor *t){
  if(t){
    free(t->form);
    free(t->form_cascade);
    free(t);
  }
}

//Does not allocate nor initialize data 
tensor *tensor_create(FORM_ELEMENT *form, FORM_LENGTH form_length){
  if(!form || !form_length){
    return NULL;
  }
  
  tensor *t = (tensor *)malloc(sizeof(tensor));
  if(!t)
    return NULL;
 
  t->form_length = form_length;
  t->form = (FORM_ELEMENT *)malloc(form_length * sizeof(FORM_ELEMENT));
  if(!t->form){
    tensor_delete(t);
    return NULL;
  }
  
  t->form_cascade = (FORM_CASCADE_ELEMENT *)calloc(form_length, sizeof(FORM_CASCADE_ELEMENT));
  if(!t->form_cascade){
    tensor_delete(t);
    return NULL;
  }
  
  t->form_cascade[form_length-1] = form[form_length-1];
  t->form[0] = form[0];
  for(FORM_LENGTH i = form_length - 1; i > 0; i--){
    
    t->form[i] = form[i];
    
    //This if statement ensures that the next multiplication will not result in overflow
    if(form[i-1] > maxof(FORM_CASCADE_ELEMENT) / t->form_cascade[i]){
      tensor_delete(t);
      return NULL;
    }
    
    t->form_cascade[i-1] = t->form_cascade[i] * form[i-1];
  }
  
  if(t->form_cascade[0] == 0){
    tensor_delete(t);
    return NULL;
  }
  
  t->data_length = (DATA_LENGTH)t->form_cascade[0];
  
  return t;
}

tensor* tensor_create_data(tensor *t){
  if(!t){
    return NULL;
  }
  t->data = (ELEMENT *)calloc(t->data_length, sizeof(ELEMENT));
  return t->data;
}



tensor* tensor_add(tensor *A, tensor *B){
  tensor* C = tensor_create(A->form, A->form_length);
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i] + B->data[i];
  
  return C;
}


tensor* tensor_add_d_1(tensor *A, tensor *B){
  tensor* C = tensor_create(A->form, A->form_length);
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = 1;
  
  return C;
}


tensor* tensor_add_d_2(tensor *A, tensor *B){
  tensor* C = tensor_create(A->form, A->form_length);
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = 1;
  
  return C;
}


tensor* tensor_sub(tensor *A, tensor *B){
  tensor* C = tensor_create(A->form, A->form_length);
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i] - B->data[i];
  
  return C;
}

tensor* tensor_sub_d_1(tensor *A, tensor *B){
  tensor* C = tensor_create(A->form, A->form_length);
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = 1;
  
  return C;
}

tensor* tensor_sub_d_2(tensor *A, tensor *B){
  tensor* C = tensor_create(A->form, A->form_length);
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = -1;
  
  return C;
}


tensor* tensor_scale(tensor *A, ELEMENT B){
  tensor* C = tensor_create(A->form, A->form_length);
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i] * B;
  
  return C;
}

tensor* tensor_scale_d_1(tensor *A, tensor *B){
  tensor* C = tensor_create(A->form, A->form_length);
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = B->data[0];
  
  return C;
}

tensor* tensor_scale_d_2(tensor *A, tensor *B){
  tensor* C = tensor_create(A->form, A->form_length);
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i];
  
  return C;
}



tensor* tensor_full(tensor *A, tensor *B){
  tensor* C = tensor_create(&B->form[1], B->form_length-1);
  
  for(DATA_LENGTH i = 0; i < C->data_length; i++){
    for(DATA_LENGTH h = 0; h < A->data_length; h++){
      C->data[i] += A->data[h] * B->data[h + (i * A->data_length)];
    }
  }

  return C;
}

tensor* tensor_full_d_1(tensor *A, tensor *B){
  tensor* C = tensor_create(&B->form[1], B->form_length-1);
  
  for(DATA_LENGTH i = 0; i < C->data_length; i++){
    for(DATA_LENGTH h = 0; h < A->data_length; h++){
      C->data[i] += B->data[h + (i * A->data_length)];
    }
  }

  return C;
}

tensor* tensor_full_d_2(tensor *A, tensor *B){
  tensor* C = tensor_create(&B->form[1], B->form_length-1);
  
  for(DATA_LENGTH i = 0; i < C->data_length; i++){
    for(DATA_LENGTH h = 0; h < A->data_length; h++){
      C->data[i] += A->data[h];
    }
  }

  return C;
}
