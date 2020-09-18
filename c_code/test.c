#include "project.h"
#include "tensor/.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
  printf("#################### TENSOR TEST ####################\n\n");
  
  printf("Authored by Nicolas Ayala, nicoayalamag@gmail.com\n");
  printf("  EV means expected value\n\n");
  
  printf("----------Test 1/4, macros\n\n");

  printf("max of uint8_t:  %llu EV %llu\n", maxof(uint8_t)  , 255ull);
  printf("max of uint16_t: %llu EV %llu\n", maxof(uint16_t) , 65535ull);
  printf("max of uint32_t: %llu EV %llu\n", maxof(uint32_t) , 4294967295ull);
  printf("max of uint64_t: %llu EV %llu\n", maxof(uint64_t) , 18446744073709551615ull);
  printf("max of int8_t:   %llu EV %llu\n", maxof(int8_t)   , 127ull);
  printf("max of int16_t:  %llu EV %llu\n", maxof(int16_t)  , 32767ull);
  printf("max of int32_t:  %llu EV %llu\n", maxof(int32_t)  , 2147483647ull);
  printf("max of int64_t:  %llu EV %llu\n", maxof(int64_t)  , 9223372036854775807ull);
  
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
  
  printf("Testing the saving and reading of atomic types\n");
  uint8_t test[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  uint64_t index = 1;
  uint64_t index_save = index;
  uint64_t data = 0xfedcba9876543210;
  
  index_save = index;
  ELEMENT e = *(ELEMENT *) &data;
  printf("ELEMENT save %08x\n", *(uint32_t *) &e);
  save_ELEMENT(test, &index, e);
  printf("test ");
  for(int h = 0;h < 20; h++){
    printf("%02x", test[h]);
  }
  index=index_save;
  ELEMENT ef = read_ELEMENT(test, &index);
  printf("\nELEMENT fish %08x\n",*(uint32_t *) &ef);
  printf("index %lu index before %lu\n\n",index,index_save);
  
  
  index = 6;
  index_save = index;
  FORM_LENGTH fl = *(FORM_LENGTH *) &data;
  printf("FORM_LENGTH stream %02x\n", *(uint8_t *) &fl);
  save_FORM_LENGTH(test, &index, fl);
  printf("test ");
  for(int h = 0;h < 20; h++){
    printf("%02x", test[h]);
  }
  index=index_save;
  FORM_LENGTH fle = read_FORM_LENGTH(test, &index);
  printf("\nFORM_LENGTH fish %02x\n",*(uint8_t *) &fle);
  printf("index %lu index before %lu\n\n",index,index_save);
  
  
  index = 8;
  index_save = index;
  FORM_ELEMENT fe = *(FORM_ELEMENT *) &data;
  printf("FORM_ELEMENT stream %08x\n", *(uint32_t *) &fe);
  save_FORM_ELEMENT(test, &index, fe);
  printf("test ");
  for(int h = 0;h < 20; h++){
    printf("%02x", test[h]);
  }
  index=index_save;
  FORM_ELEMENT fef = read_FORM_ELEMENT(test, &index);
  printf("\nFORM_ELEMENT fish %08x\n",*(uint32_t *) &fef);
  printf("index %lu index before %lu\n\n",index,index_save);
  
  
  index = 3;
  index_save = index;
  DATA_LENGTH dl = *(DATA_LENGTH *) &data;
  printf("DATA_LENGTH stream %08x\n", *(uint32_t *) &dl);
  save_DATA_LENGTH(test, &index, dl);
  printf("test ");
  for(int h = 0;h < 20; h++){
    printf("%02x", test[h]);
  }
  index=index_save;
  DATA_LENGTH dlf = read_DATA_LENGTH(test, &index);
  printf("\nDATA_LENGTH fish %08x\n",*(uint32_t *) &dlf);
  printf("index %lu index before %lu\n\n",index,index_save);
   
  printf("TESTING save_tensor and read_tensor\n");
  printf("tensor D:\n");
  tensor_print(D, "f");
  printf("Form length: %d form:\n", D->form_length);
  for(int i = 0; i < D->form_length; i++){
    printf("%d, ", D->form[i]);
  }
  printf("\n\n");
  
  if(tensor_save("snore", D))
    printf("Successfully saved D\n");
  else
    printf("Failed to save D\n");
  
  tensor *D_uncovered = tensor_read("snore");
  
  if(D_uncovered){
    printf("Successfully read D\n");
    printf("Uncovered D:\n");
    tensor_print(D_uncovered, "f");
  }else
    printf("Failed to read D\n");
  
  
  
  tensor_delete_data(D_uncovered);
  tensor_delete(D_uncovered);
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
