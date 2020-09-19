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
  printf("max of int64_t:  %llu EV %llu\n\n", maxof(int64_t)  , 9223372036854775807ull);
  
  printf("Type code of uint8_t: %u EV %d\n",typecode(uint8_t),4);
  printf("Type code of uint16_t: %u EV %d\n",typecode(uint16_t),8);
  printf("Type code of uint32_t: %u EV %d\n",typecode(uint32_t),16);
  printf("Type code of uint64_t: %u EV %d\n",typecode(uint64_t),32);
  printf("Type code of int8_t: %u EV %d\n",typecode(int8_t),6);
  printf("Type code of int16_t: %u EV %d\n",typecode(int16_t),10);
  printf("Type code of int32_t: %u EV %d\n",typecode(int32_t),18);
  printf("Type code of int64_t: %u EV %d\n",typecode(int64_t),34);
  printf("Type code of float: %u EV %d\n",typecode(float),19);
  printf("Type code of double: %u EV %d\n\n",typecode(double),35);
  
  printf("----------Test 2/4, Creating and printing tensor\n\n");
  
  printf(" Creating Tensor A, A is expected to succeed\n");
  
  FORM_LENGTH a_form_length = 2;
  FORM_ELEMENT a_form[2] = {2, 3};

  ELEMENT a_data[6] = {-1, 2,-3,
                        4,-5, 6};

  tensor *A = tensor_create(a_form, a_form_length);
  if(!A){
    printf(" Failed to create A\n");
    return 1;
  }
  A->data = a_data;
  
  printf(" A successfully created\n");
  printf(" Form:\n ");
  for(FORM_LENGTH i = 0; i < A->form_length; i++){
    printf("%d, ", A->form[i]);
  }
  printf("\n  EV: 2, 3\n\n");
  
  printf(" Form cascade:\n ");
  for(FORM_LENGTH i = 0; i < A->form_length; i++){
    printf("%d, ", A->form_cascade[i]);
  }
  printf("\n  EV: 6, 3\n\n");
  printf(" Testing tensor print on A:\n");
  tensor_print(A, "f");
  printf(" EV: {{-1, 2, -3},\n"); 
  printf("     {4, -5, 6}}\n\n");
  
  printf(" Creating Tensor OF, OF is expected to fail due to form_cascade overflow\n");
  
  FORM_LENGTH OF_form_length = 4;
  FORM_ELEMENT OF_form[4] = {maxof(FORM_ELEMENT),maxof(FORM_ELEMENT),maxof(FORM_ELEMENT),maxof(FORM_ELEMENT)};
  
  tensor *OF = tensor_create(OF_form, OF_form_length);
  
  if(!OF){
    printf(" OF Failed\n");
  }else{
    printf(" OF Succeded\n");
    return 2;
  }
  printf("\n");
  
  printf("----------Test 3/4, Tensor operations\n\n");
  
  printf("..... Addition, subtraction, and scaling on Tensors A and B resulting in C\n\n");
  
  
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

  printf("Tensor A:\n");
  tensor_print(A, "f");
  printf("Tensor B:\n");
  tensor_print(B, "f");
  
  tensor *C = tensor_create(a_form, a_form_length);
  tensor_create_data(C);  
  
  printf("\nPairwise sum of elements from A and B\n");
  printf("tensor_add(C,A,B):\n");
  tensor_add(C,A,B);
  tensor_print(C, "f");
  
  printf("\nPairwise subtraction of elements from A and B\n");
  printf("tensor_sub(C,A,B):\n");
  tensor_sub(C,A,B);
  tensor_print(C, "f");
  
  printf("\nScaling of elements of A by first element of B\n");
  printf("tensor_scale(C,A,B):\n");
  tensor_scale(C,A,B);
  tensor_print(C, "f");
  
  printf("\n..... Fully connected operation on layer A with parameters D resulting in E\n\n");
  FORM_ELEMENT D_form[3] = {A->data_length, 2, 2};
  tensor *D = tensor_create(D_form, 3);
  tensor_create_data(D);
  
  for(DATA_LENGTH i = 0; i < D->data_length; i++){
    D->data[i] =  i;
  }
   
  tensor *E = tensor_full_create(A, D);
  
  tensor_full(E,A,D);
  printf("A:\n");
  tensor_print(A, "f");

  printf("\nD:\n");
  tensor_print(D, "f");
  
  printf("\nE:\n");
  tensor_print(E, "f");
  
  printf("\n----------Test 4/4, saving and reading\n\n");

  uint8_t test[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  uint64_t index = 1;
  uint64_t index_save = index;
  uint64_t data = 0xfedcba9876543210;
  
  index_save = index;
  ELEMENT e = *(ELEMENT *) &data;
  printf("ELEMENT save %08x\n", *(uint32_t *) &e);
  save_ELEMENT(test, &index, e);
  index=index_save;
  ELEMENT ef = read_ELEMENT(test, &index);
  printf("ELEMENT read %08x\n",*(uint32_t *) &ef);
  printf("index: %lu index before: %lu\n",index,index_save);
  printf("index should have increased by %lu\n\n", sizeof(ELEMENT));
  
  index = 6;
  index_save = index;
  FORM_LENGTH fl = *(FORM_LENGTH *) &data;
  printf("FORM_LENGTH save %02x\n", *(uint8_t *) &fl);
  save_FORM_LENGTH(test, &index, fl);
  index=index_save;
  FORM_LENGTH fle = read_FORM_LENGTH(test, &index);
  printf("FORM_LENGTH fish %02x\n",*(uint8_t *) &fle);
  printf("index: %lu index before: %lu\n",index,index_save);
  printf("index should have increased by %lu\n\n", sizeof(FORM_LENGTH));
  
  index = 8;
  index_save = index;
  FORM_ELEMENT fe = *(FORM_ELEMENT *) &data;
  printf("FORM_ELEMENT save %08x\n", *(uint32_t *) &fe);
  save_FORM_ELEMENT(test, &index, fe);
  index=index_save;
  FORM_ELEMENT fef = read_FORM_ELEMENT(test, &index);
  printf("FORM_ELEMENT read %08x\n",*(uint32_t *) &fef);
  printf("index: %lu index before: %lu\n",index,index_save);
  printf("index should have increased by %lu\n\n", sizeof(FORM_ELEMENT));
  
  index = 3;
  index_save = index;
  DATA_LENGTH dl = *(DATA_LENGTH *) &data;
  printf("DATA_LENGTH save %08x\n", *(uint32_t *) &dl);
  save_DATA_LENGTH(test, &index, dl);
  index=index_save;
  DATA_LENGTH dlf = read_DATA_LENGTH(test, &index);
  printf("DATA_LENGTH read %08x\n",*(uint32_t *) &dlf);
  printf("index: %lu index before: %lu\n",index,index_save);
  printf("index should have increased by %lu\n\n", sizeof(DATA_LENGTH));

  printf("TESTING save_tensor and read_tensor by saving and uncovering D\n\n");
  printf("tensor D:\n");
  tensor_print(D, "f");
  printf("Form length: %d form:\n", D->form_length);
  for(int i = 0; i < D->form_length; i++){
    printf("%d, ", D->form[i]);
  }
  printf("\n\n");
  
  if(tensor_save("D_file", D))
    printf("Successfully saved D into D_file\n");
  else
    printf("Failed to save D\n");
  
  tensor *new_D = tensor_read("D_file");
  
  if(new_D){
    printf("Successfully read D_file into new_D\n");
    printf("new_D:\n");
    tensor_print(new_D, "f");
  }else
    printf("Failed to read D_file\n");
  
  
  
  tensor_delete_data(new_D);
  tensor_delete(new_D);
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
