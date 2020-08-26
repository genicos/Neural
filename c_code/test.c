#include "project.h"
#include "tensor.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
  printf("max of uint8_t:  %llu \n", maxof(uint8_t)  );
  printf("max of uint16_t: %llu \n", maxof(uint16_t) );
  printf("max of uint32_t: %llu \n", maxof(uint32_t) );
  printf("max of uint64_t: %llu \n", maxof(uint64_t) );
  printf("max of int8_t:   %llu \n", maxof(int8_t)   );
  printf("max of int16_t:  %llu \n", maxof(int16_t)  );
  printf("max of int32_t:  %llu \n", maxof(int32_t)  );
  printf("max of int64_t:  %llu \n", maxof(int64_t)  );
  
  FORM_LENGTH a_form_length = 2;
  FORM_ELEMENT a_form[2] = {2, 3};

  ELEMENT a_data[6] = {-1, 2,-3,
                        4,-5, 6};

  tensor *A = tensor_create(a_form, a_form_length);
  if(!A){
    printf("Failed to create A\n");
    return 1;
  }
  A->data = a_data;
  
  printf("A successfully created\n");
  printf(" Form:\n ");
  for(FORM_LENGTH i = 0; i < A->form_length; i++){
    printf("%d, ", A->form[i]);
  }
  printf("\n Form cascade:\n ");
  for(FORM_LENGTH i = 0; i < A->form_length; i++){
    printf("%d, ", A->form_cascade[i]);
  }
  printf("\n Contents of data:\n");
  tensor_print(A, "f");
  
  FORM_LENGTH b_form_length = 2;
  FORM_ELEMENT b_form[2] = {2, 3};
  
  ELEMENT b_data[6] = { 2,-3, 4,
                       -5, 6,-7};
  
  tensor *B = tensor_create(b_form, b_form_length);
  if(!B){
    printf("Failed to create B\n");
    return 1;
  }
  B->data = b_data;
  printf("B data:\n");
  tensor_print(B, "f");
  
  tensor *C = tensor_create(a_form, a_form_length);
  tensor_create_data(C);  
  
  printf("tensor_add(C,A,B):\n");
  tensor_add(C,A,B);
  tensor_print(C, "f");
  
  printf("tensor_sub(C,A,B):\n");
  tensor_sub(C,A,B);
  tensor_print(C, "f");
  
  printf("tensor_scale(C,A,B):\n");
  tensor_scale(C,A,B);
  tensor_print(C, "f");
  
  printf("\nTesting fully connected layer\n\n");
  FORM_ELEMENT D_form[3] = {A->data_length, 2, 2};
  tensor *D = tensor_create(D_form, 3);
  tensor_create_data(D);
  
  for(DATA_LENGTH i = 0; i < D->data_length; i++){
    D->data[i] =  i;
  }
   
  tensor *E = tensor_full_create(A, D);
  
  tensor_full(E,A,D);
  printf("A\n"); 
  tensor_print(A, "f");

  printf("D\n");
  tensor_print(D, "f");
  
  printf("E\n");
  tensor_print(E, "f");
  
  tensor_delete_data(E);
  tensor_delete(E);
  tensor_delete_data(D);
  tensor_delete(D);
  tensor_delete_data(C);
  tensor_delete(C);
  tensor_delete(B);
  tensor_delete(A); 
  return 0; 
}
