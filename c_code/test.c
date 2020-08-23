#include "project.h"
#include "tensor.h"
#include <inttypes.h>
#include <stdio.h>

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
  
  
  
  FORM_LENGTH b_form_length = 2;
  FORM_ELEMENT b_form[2] = {2, 3};
  
  ELEMENT b_data[6] = { 1,-2, 3,
                       -4, 5,-6};
  
  tensor *B = tensor_create(b_form, b_form_length);
  if(!B){
    printf("Failed to create B\n");
    return 1;
  }
  B->data = b_data;
  
  tensor *C = tensor_create(a_form, a_form_length);
  tensor_create_data(C);
  
  tensor_add(C,A,B);
  tensor_print(C, "f");
  
  tensor_delete_data(C);
  tensor_delete(C);
  tensor_delete(B);
  tensor_delete(A); 
  return 0; 
}
