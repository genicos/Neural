#include "../../project.h"
#include "../../tensor/tensor.h"
#include "../../tensor/functions.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(){
  
  //Creating 4 pairs of identical tensors, to test tensor_equal

  FORM_LENGTH  E_1a_form_length = 2;
  FORM_ELEMENT E_1a_form[2]     = {2,2};
  ELEMENT      E_1a_data[4]     = {1,2,3,4};
  tensor      *E_1a             = tensor_create(2, E_1a_form);
  E_1a->data = E_1a_data;

  FORM_LENGTH  E_1b_form_length = 2;
  FORM_ELEMENT E_1b_form[2]     = {2,2};
  ELEMENT      E_1b_data[4]     = {1,2,3,4};
  tensor      *E_1b             = tensor_create(2, E_1b_form);
  E_1b->data = E_1b_data;


  FORM_LENGTH  E_2a_form_length = 3;
  FORM_ELEMENT E_2a_form[3]     = {2,1,2};
  ELEMENT      E_2a_data[4]     = {88,20,6.5,4};
  tensor      *E_2a             = tensor_create(3, E_2a_form);
  E_2a->data = E_2a_data;
  
  FORM_LENGTH  E_2b_form_length = 3;
  FORM_ELEMENT E_2b_form[3]     = {2,1,2};
  ELEMENT      E_2b_data[4]     = {88,20,6.5,4};
  tensor      *E_2b             = tensor_create(3, E_2b_form);
  E_2b->data = E_2b_data;


  FORM_LENGTH  E_3a_form_length = 3;
  FORM_ELEMENT E_3a_form[3]     = {3,4,2};
  ELEMENT      E_3a_data[24]    = 
    {-3,4,43,9,0.5,-9,55.3,89.2,-54.2,7,12,-39,90,0.043,65.3,83,-48.3,30,4,-2,3.3,55,-4,6.7};
  tensor      *E_3a             = tensor_create(3, E_3a_form);
  E_3a->data = E_3a_data;

  FORM_LENGTH  E_3b_form_length = 3;
  FORM_ELEMENT E_3b_form[3]     = {3,4,2};
  ELEMENT      E_3b_data[24]    = 
    {-3,4,43,9,0.5,-9,55.3,89.2,-54.2,7,12,-39,90,0.043,65.3,83,-48.3,30,4,-2,3.3,55,-4,6.7};
  tensor      *E_3b             = tensor_create(3, E_3b_form);
  E_3b->data = E_3b_data;


  FORM_LENGTH  E_4a_form_length = 1;
  FORM_ELEMENT E_4a_form[1]     = {6};
  ELEMENT      E_4a_data[6]     = {8,-39,9.9,0,82,3.2};
  tensor      *E_4a             = tensor_create(1, E_4a_form);
  E_4a->data = E_4a_data;

  FORM_LENGTH  E_4b_form_length = 1;
  FORM_ELEMENT E_4b_form[1]     = {6};
  ELEMENT      E_4b_data[6]     = {8,-39,9.9,0,82,3.2};
  tensor      *E_4b             = tensor_create(1, E_4b_form);
  E_4b->data = E_4b_data;
  

  //Comparing equal pairs
  bool E1 = tensor_equal(E_1a,E_1b);
  bool E2 = tensor_equal(E_2a,E_2b);
  bool E3 = tensor_equal(E_3a,E_3b);
  bool E4 = tensor_equal(E_4a,E_4b);
  
  if(!E1 || !E2 || !E3 || !E4){
    printf("tensor_equal failed to call equal tensors equal ! ! ! ! ! !");
    printf("FAIL\n");
    return 1;
  }
  
  //Altering data of b sides of pairs, so that pairs are no longer equal
  E_1b->data[0]++;
  E_2b->data[0]++;
  E_3b->data[0]++;
  E_4b->data[0]++;
  
  bool NE1 = tensor_equal(E_1a,E_1b);
  bool NE2 = tensor_equal(E_2a,E_2b);
  bool NE3 = tensor_equal(E_3a,E_3b);
  bool NE4 = tensor_equal(E_4a,E_4b);
  
  if(NE1 || NE2 || NE3 || NE4){
    printf("tensor_equal failed to call unequal tensors unequal ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 1;
  }
  
  if(!tensor_equal(NULL,NULL) || tensor_equal(E_1a, NULL) || tensor_equal(NULL, E_1a)){
    printf("tensor_equal failed to account for NULL pointers ! ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 1;
  }
  
  tensor_delete(E_1a);
  tensor_delete(E_1b);
  tensor_delete(E_2a);
  tensor_delete(E_2b);
  tensor_delete(E_3a);
  tensor_delete(E_3b);
  tensor_delete(E_4a);
  tensor_delete(E_4b);
  
  printf("tensor_equal passed.\n");


  //Saving and recovering a tensor  
  
  FORM_LENGTH  IO_form_length = 3;
  FORM_ELEMENT IO_form[3]     = {2,2,2};
  tensor      *IO             = tensor_create(IO_form_length, IO_form);
  ELEMENT      IO_data[8]     = {23.23,45.2,123.5,87.3,3.67,87.3,65.25,34.66};
  IO->data                    = IO_data;
  
  if(!tensor_save("TENSOR_TEST_SAVE",IO)){
    printf("tensor_save failed ! ! ! ! ! ! ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 2;
  }
  
  tensor *IO_recovered = tensor_read("TENSOR_TEST_SAVE");
  
  if(!tensor_equal(IO,IO_recovered)){
    printf("tensor_save or tensor_read failed, recovered tensor is altered ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 1;
  }
  
  tensor_delete(IO);
  tensor_delete(IO_recovered);
 
  printf("tensor_save and tensor_read passed\n");
  
  

  FORM_ELEMENT T_form[2]     = {4,16};
  tensor      *T             = tensor_create(2, T_form);
  ELEMENT      T_data[64]     =
  {1,0,0,0,2,0,0,0,3,0,0,0,4,0,0,0,
   0,1,0,0,0,2,0,0,0,3,0,0,0,4,0,0,
   0,0,1,0,0,0,2,0,0,0,3,0,0,0,4,0,
   0,0,0,1,0,0,0,2,0,0,0,3,0,0,0,4};
  T->data                    = T_data;
  
  //tensor_save("src/test/tensor/OUT/3/AD_d2",T);
  tensor_print(T, "f"); 
  tensor_delete(T);
  
  //testing every function 
  
  char *IN_path  = "src/test/tensor/IN";
  char *OUT_path = "src/test/tensor/OUT";
  char buffer[256];
  struct dirent *dir;
   
  DIR *OUT = opendir(OUT_path);
  if(!OUT){
    printf("Missing directory neccessary for testing: src/test/tensor/OUT ! ! ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 1;
  }

  DIR *IN = opendir(IN_path);
  if(!IN){
    printf("Missing directory neccessary for testing: src/test/tensor/IN ! ! ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 1;
  }
  
  
  while((dir = readdir(OUT)) != NULL){ //Finding directories with function output examples
    
    if(dir->d_type == DT_DIR && dir->d_name[0] != '.'){
      
      uint64_t func_num = atoi(dir->d_name);
      
      snprintf(buffer, sizeof(buffer), "%s/%s", OUT_path, dir->d_name);//loading full path into buffer
      printf("RR %s\n", buffer);
      
      DIR *func = opendir(buffer);
      if(!func){
        printf("Failed to find directory that should exist, test_tensor is at fault ! ! ! ! ! !\n");
        printf("FAIL\n");
        return 1;
      }
      
      char buffer_2[256];
      
      while((dir = readdir(func)) != NULL){ //Looping through given output examples, trying to replicate them
        if(dir->d_type == DT_REG){
          printf("  %s \n", dir->d_name);

           
          snprintf(buffer_2, sizeof(buffer_2),"%s/%c", IN_path, dir->d_name[0]);
          tensor *arg_1 = tensor_read(buffer_2);
          printf(" buffer_2 %s\n", buffer_2);

          snprintf(buffer_2, sizeof(buffer_2),"%s/%c", IN_path, dir->d_name[1]);
          tensor *arg_2 = tensor_read(buffer_2);
          printf(" buffer_2 %s\n", buffer_2);

          printf(" buffer %s\n", buffer); 
          snprintf(buffer_2, sizeof(buffer_2),"%s/%s", buffer, dir->d_name);
          tensor *ans = tensor_read(buffer_2);
          printf(" buffer_2 %s\n", buffer_2);
          
           
          if(!(ans && arg_1 && arg_2)){
            printf("Failed to read example tensors, test_tensor is at fault ! ! ! ! !\n");
            printf("FAIL\n");
            return 1;
          }
          
          
          tensor *my_ans = tensor_function_table[func_num]->create(arg_1, arg_2);
         
          if(dir->d_name[2] == '_'){ //partial derivative test
            
            //tensor *my_partial = tensor_cartesian_product(my_ans, 
          }else{
            tensor_function_table[func_num]->f(my_ans,arg_1,arg_2);
            
            if(!tensor_equal(ans,my_ans)){  
              printf("Failed on function %lu, example %s\n", func_num, buffer_2);
              printf("Program tensor:\n");
              tensor_print(my_ans, "f");
              printf("Ground truth:\n");
              tensor_print(ans, "f");

              return 1;
            }
          }
          tensor_delete(my_ans);
          
          tensor_delete(ans);
          tensor_delete(arg_1);
          tensor_delete(arg_2);
        }
      }
      closedir(func);
    }
  }
  closedir(OUT);
  closedir(IN);
  
  
  
  //printf("GOOG %d %d\n", tensor_function_table[0]->pairwise_to_first, FUNCTION_CT);
  
  printf("#################### TENSOR TEST ####################\n\n");
  
  printf("Authored by Nicolas Ayala, nicoayalamag@gmail.com\n");
  printf("  EV means expected value\n\n");
  
  printf("----------Test 1/5, macros\n\n");

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
  
  printf("----------Test 2/5, Creating and printing tensor\n\n");
  
  printf(" Creating Tensor A, A is expected to succeed\n");
  
  FORM_LENGTH a_form_length = 2;
  FORM_ELEMENT a_form[2] = {2, 3};

  ELEMENT a_data[6] = {-1, 2,-3,
                        4,-5, 6};

  tensor *A = tensor_create(a_form_length, a_form);
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
  
  tensor *OF = tensor_create(OF_form_length, OF_form);
  
  if(!OF){
    printf(" OF Failed\n");
  }else{
    printf(" OF Succeded\n");
    return 2;
  }
  printf("\n");
  
  printf("----------Test 3/5, Tensor operations\n\n");
  
  printf("..... Addition, subtraction, and scaling on Tensors A and B resulting in C\n\n");
  
  
  FORM_LENGTH b_form_length = 2;
  FORM_ELEMENT b_form[2] = {2, 3};
  
  ELEMENT b_data[6] = { 2,-3, 4,
                       -5, 6,-7};
  
  tensor *B = tensor_create(b_form_length, b_form);
  if(!B){
    printf("Failed to create B\n");
    return 1;
  }
  B->data = b_data;

  printf("Tensor A:\n");
  tensor_print(A, "f");
  printf("Tensor B:\n");
  tensor_print(B, "f");
  
  tensor *C = tensor_create(a_form_length, a_form);
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
  tensor *D = tensor_create(3,D_form);
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
  
  printf("\n----------Test 4/5, saving and reading\n\n");

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
  }else{
    printf("Failed to read D_file\n");
  }


  printf("\n----------Test 5/5, function_table\n\n"); 
 
  FORM_ELEMENT F_form[1] = {2};
  ELEMENT F_data[2] = {1,2};
  
  FORM_ELEMENT G_form[2] = {2,2};
  ELEMENT G_data[4] = {1,2,3,4};
  
  
  tensor *F = tensor_create(1,F_form);
  tensor *G = tensor_create(2,G_form);
  
  if(!F || !G){
    printf("Fail: tensor_create\n");
    return 1;
  }
  
  F->data = F_data;
  G->data = G_data;
  
  printf("F:\n");
  tensor_print(F, "f");

  printf("G:\n");
  tensor_print(G, "f");
  
  //
  for(int i = 0; i < FUNCTION_CT; i++){
    printf("Function %d\n",i);
    
    printf("creating H with tensor_function_table[%d]->create\n", i);
    tensor *H = tensor_function_table[i]->create(F,G);    
    if(!H){
      tensor_delete(F);
      tensor_delete(G);
      printf("Failed to create H\n");
      return 1;
    }
    printf("Successfully created H\n");



    printf("\ntensor_function_table[%d]->f(H,F,G)\n", i);
    tensor_function_table[i]->f(H,F,G);
    
    printf("H:\n");
    tensor_print(H, "f");
    

    tensor *cart_HF = tensor_cartesian_product(H,F);
    if(!cart_HF){
      tensor_delete(H);
      tensor_delete(F);
      tensor_delete(G);
      printf("Failed to create cart_HF\n");
    }

    printf("\ntensor_function_table[%d]->f_d_1(cart_HF,F,G)\n", i);
    tensor_function_table[i]->f_d_1(cart_HF,F,G);
    
    printf("cart_HF:\n");
    tensor_print(cart_HF, "f");
    

    tensor *cart_HG = tensor_cartesian_product(H,G);
    if(!cart_HG){
      tensor_delete(cart_HG);
      tensor_delete(H);
      tensor_delete(F);
      tensor_delete(G);
      printf("Failed to create cart_HF\n");
    }

    printf("\ntensor_function_table[%d]->f_d_2(cart_HG,F,G)\n", i);
    tensor_function_table[i]->f_d_2(cart_HG,F,G);
    
    printf("cart_HG:\n");
    tensor_print(cart_HG, "f");

    tensor_delete(H);
    tensor_delete(cart_HF);
    tensor_delete(cart_HG);
  }
  //
  
  tensor_delete(G);
  tensor_delete(F); 
  tensor_delete(new_D);
  tensor_delete(E);
  tensor_delete(D);
  tensor_delete(C);
  tensor_delete(B);
  tensor_delete(A);
 
  return 0; 
}
