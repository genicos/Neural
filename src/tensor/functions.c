#include "functions.h"
//#include <stdio.h>

const tensor_function add = {
  
  .f     = &tensor_add,
  .f_d_1 = &tensor_add_d_1,
  .f_d_2 = &tensor_add_d_2,
  
  .create = &tensor_add_create,
  
  .pairwise_to_first = true,
  .pairwise_to_second = true,
};


const tensor_function sub = {
  
  .f     = &tensor_sub,
  .f_d_1 = &tensor_sub_d_1,
  .f_d_2 = &tensor_sub_d_2,
  
  .create = &tensor_sub_create,
  
  .pairwise_to_first = true,
  .pairwise_to_second = true,
};

const tensor_function scale = {
  
  .f     = &tensor_scale,
  .f_d_1 = &tensor_scale_d_1,
  .f_d_2 = &tensor_scale_d_2,
  
  .create = &tensor_scale_create,
  
  .pairwise_to_first = true,
  .pairwise_to_second = false,
};


const tensor_function full = {
  
  .f     = &tensor_full,
  .f_d_1 = &tensor_full_d_1,
  .f_d_2 = &tensor_full_d_2,
  
  .create = &tensor_full_create,

  .pairwise_to_first  = false,
  .pairwise_to_second = false,
};


const tensor_function *tensor_function_table[FUNCTION_CT] = {
  &add,
  &sub, 
  &scale, 
  &full,
};



tensor* tensor_cartesian_product(tensor *A, tensor *B){
  if(!A || !B){
    return NULL;
  }
  FORM_ELEMENT c_form[2] = {A->data_length, B->data_length};

  tensor *C = tensor_create(2, c_form);
  tensor_create_data(C); 

  return C;
}

tensor* tensor_chain_rule(tensor *AB, tensor *BC){
  if(!AB || !BC){
    return NULL;
  }
  FORM_ELEMENT AC_form[2] = {AB->form[0], BC->form[1]};
  
  tensor *AC = tensor_create(2, AC_form);
  tensor_create_data(AC);
  
  if(!AC){
    return NULL;
  }
  
  for(FORM_ELEMENT a = 0; a < AC->form[0]; a++){
    for(FORM_ELEMENT b = 0; b < AB->form[1]; b++){
      for(FORM_ELEMENT c = 0; c < BC->form[1]; c++){
        AC->data[a*AC->form[1] + c] +=
          AB->data[a*AB->form[1] + b] *
          BC->data[b*BC->form[1] + c];
      }
    }
  }
  
  return AC;
}

tensor *tensor_zero(FORM_LENGTH form_length, FORM_ELEMENT *form){
  tensor *ans = tensor_create(form_length, form);
  tensor_create_data(ans);
  
  return ans;
}

tensor *tensor_identity(FORM_ELEMENT s){
  
  FORM_ELEMENT form[2] = {s,s};  //A matrix
  
  tensor *ans = tensor_zero(2, form);  //zero matrix
  if(!ans)
    return NULL;

  for(FORM_ELEMENT i = 0; i < s; i++){  //with 1's on main diagonal
    ans->data[i*s + i] = 1;
  }
  
  return ans;
}





tensor* tensor_add(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i] + B->data[i];
  
  return C;
}

tensor* tensor_add_d_1(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < C->form[0]; i++)
    C->data[i*C->form[1] + i] = 1;
  
  return C;
}

tensor* tensor_add_d_2(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < C->form[0]; i++)
    C->data[i*C->form[1] + i] = 1;
  
  return C;
}

tensor* tensor_add_create(tensor *A, tensor *B){
  tensor *C = tensor_create(A->form_length, A->form);
  tensor_create_data(C);
  
  return C;
}






tensor* tensor_sub(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i] - B->data[i];
  
  return C;
}

tensor* tensor_sub_d_1(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < C->form[0]; i++)
    C->data[i*C->form[1] + i] = 1;
  
  return C;
}

tensor* tensor_sub_d_2(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < C->form[0]; i++)
    C->data[i*C->form[1] + i] = -1;
  
  return C;
}

tensor* tensor_sub_create(tensor *A, tensor *B){
  tensor *C = tensor_create(A->form_length, A->form);
  tensor_create_data(C);
  
  return C;
}



tensor* tensor_scale(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i] * B->data[0];
  
  return C;
}

tensor* tensor_scale_d_1(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < C->form[0]; i++)
    C->data[i*C->form[1] + i] = B->data[0];
  
  return C;
}

tensor* tensor_scale_d_2(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < C->form[0]; i++)
    C->data[i*C->form[1]] = A->data[i];
  
  return C;
}

tensor* tensor_scale_create(tensor *A, tensor *B){
  tensor *C = tensor_create(A->form_length, A->form);
  tensor_create_data(C);
  
  return C;
}



tensor* tensor_full(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < C->data_length; i++){
    for(DATA_LENGTH h = 0; h < A->data_length; h++){
      C->data[i] += A->data[h] * B->data[i + (h * C->data_length)];
      
    }
  }

  return C;
}

tensor* tensor_full_d_1(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < C->form[0]; i++){
    for(DATA_LENGTH h = 0; h < C->form[1]; h++){
      C->data[i*C->form[0] + h] = B->data[h*C->form[1] + i]; //B and C use swapped coords
    }
  }

  return C;
}

tensor* tensor_full_d_2(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++){
    for(DATA_LENGTH j = 0; j < C->form[0]; j++){
      C->data[j*C->form[1] + j + i*C->form[0]] = A->data[i];
    }
  }

  return C;
}

tensor* tensor_full_create(tensor *A, tensor *B){

  if(B->form_length < 2)
    return false;

  tensor *C = tensor_create(B->form_length-1, &B->form[1]); //test for correct form
  tensor_create_data(C);
  
  return C;
}
