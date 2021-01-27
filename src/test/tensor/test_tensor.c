#include "../../project.h"
#include "../../tensor/tensor.h"
#include "../../tensor/functions.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include <math.h>

int main(){
  
  printf("\nTesting tensor\n");
  
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
    printf("tensor_equal failed to call equal tensors equal ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 1;
  }
  
  //Altering data of b sides of pairs, so that pairs are no longer equal
  E_1b->data[0]++;
  E_2b->data[0]++;
  E_3b->data[0]++;
  E_4b->data[0]++;
  
  bool nE1 = tensor_equal(E_1a,E_1b);
  bool nE2 = tensor_equal(E_2a,E_2b);
  bool nE3 = tensor_equal(E_3a,E_3b);
  bool nE4 = tensor_equal(E_4a,E_4b);
  
  if(nE1 || nE2 || nE3 || nE4){
    printf("tensor_equal failed to call unequal tensors unequal ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 1;
  }
  
  if(!tensor_equal(NULL,NULL) || tensor_equal(E_1a, NULL) || tensor_equal(NULL, E_1a)){
    printf("tensor_equal failed to account for NULL pointers ! ! ! ! ! ! !\n");
    printf("FAIL\n");
    return 1;
  }
  
  tensor *copy = tensor_copy(E_1a);
  if(!tensor_equal(copy, E_1a)){
    printf("Tensor copy failed ! ! ! ! ! ! ! ! \n");
    printf("FAIL\n");
    return 1;
  }
  printf("tensor_copy passed.\n");
  tensor_delete(copy);
  
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
  
  tensor_save("TENSOR_TEST_SAVE2", IO_recovered);
  
  tensor_delete(IO);
  tensor_delete(IO_recovered);
 
  printf("tensor_save and tensor_read passed\n");
  
  
  /*                                      //To add new tests
  FORM_ELEMENT T_form[2]     = {4,4};
  tensor      *T             = tensor_create(2, T_form);
  
  float S = (float)(M_E+M_E*M_E + M_E*M_E*M_E + M_E*M_E*M_E*M_E);
  
  ELEMENT help[4] = 
  {(float)(M_E/S), (float)(M_E*M_E/S), (float)(M_E*M_E*M_E/S), (float)(M_E*M_E*M_E*M_E/S)};
  
  ELEMENT      T_data[16]     =
  {help[0]*(1-help[0]), -help[0]*help[1], -help[0]*help[2], -help[0]*help[3] ,
   -help[1]*help[0], help[1]*(1-help[1]), -help[1]*help[2], -help[1]*help[3],
   -help[2]*help[0], -help[2]*help[1], help[2]*(1-help[2]),  -help[2]*help[3],
   -help[3]*help[0], -help[3]*help[1], -help[3]*help[2], help[3]*(1-help[3])};
  T->data                    = T_data;
  
  tensor_save("src/test/tensor/OUT/5/AA_d1",T);
  tensor_print(T, "f"); 
  tensor_delete(T);
  */


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

    
    if(dir->d_type == DT_DIR && dir->d_name[0] != '.'){ //Ensuring files are not dot directories
      
      uint64_t func_num = atoi(dir->d_name);   //Functions are either numbered, or special
      char special_func = dir->d_name[0];      //
      
      snprintf(buffer, sizeof(buffer), "%s/%s", OUT_path, dir->d_name);//loading full path into buffer
      
      DIR *func = opendir(buffer);
      if(!func){
        printf("Failed to find directory that should exist, test_tensor is at fault ! ! ! ! ! !\n");
        printf("FAIL\n");
        return 1;
      }
      
      char buffer_2[256];
      
      while((dir = readdir(func)) != NULL){ //Looping through given output examples, trying to replicate them
        if(dir->d_type == DT_REG){
           
          snprintf(buffer_2, sizeof(buffer_2),"%s/%c", IN_path, dir->d_name[0]);
          tensor *arg_1 = tensor_read(buffer_2);

          snprintf(buffer_2, sizeof(buffer_2),"%s/%c", IN_path, dir->d_name[1]);
          tensor *arg_2 = tensor_read(buffer_2);          
 
          snprintf(buffer_2, sizeof(buffer_2),"%s/%s", buffer, dir->d_name);
          tensor *ans = tensor_read(buffer_2);
          
          
           
          if(!(ans && arg_1 && arg_2)){
            printf("Failed to read example tensors, test_tensor is at fault ! ! ! ! !\n");
            printf("FAIL\n");
            return 1;
          }
          
          
          tensor *my_ans = tensor_function_table[func_num]->create(arg_1, arg_2);
          
          if(special_func == 'c'){                 //chain rule test
            
            tensor *chain = tensor_chain_rule(arg_1, arg_2);
            
            if(!tensor_equal(ans, chain)){
              printf("Failed on chain rule, example %s\n ! ! ! ! ! ! ! ! !\n", buffer_2);
              printf("Program tensor:\n");
              tensor_print(chain, "f");
              printf("Ground truth:\n");
              tensor_print(ans, "f");
              return 1;
            }
            
            
            tensor_delete(chain);
            
          }else if(dir->d_name[2] == '_'){       //partial derivative test
            
            tensor *my_partial;
            
            if(dir->d_name[4] == '1'){                                          //In terms of arg 1
              my_partial = tensor_cartesian_product(my_ans, arg_1);
              tensor_function_table[func_num]->f_d_1(my_partial, arg_1, arg_2);
            }else{                                                              //In terms of arg 2
              my_partial = tensor_cartesian_product(my_ans, arg_2);
              tensor_function_table[func_num]->f_d_2(my_partial, arg_1, arg_2);
            } 
            
            if(!tensor_equal(ans,my_partial)){  
              printf("Failed on derivative of function %lu, example %s\n ! ! ! ! ! ! ! ! !\n", func_num, buffer_2);
              printf("Program tensor:\n");
              tensor_print(my_partial, "f");
              printf("Ground truth:\n");
              tensor_print(ans, "f");
              return 1;
            }
            
            tensor_delete(my_partial); 
          }else{                          //regular function test
            
            tensor_function_table[func_num]->f(my_ans,arg_1,arg_2);
            
            if(!tensor_equal(ans,my_ans)){  
              printf("Failed on function %lu, example %s\n ! ! ! ! ! ! ! ! !\n", func_num, buffer_2);
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
      
      if(special_func == 'c'){
        printf("Chain rule passed.\n");
      }else{
        printf("Function %lu passed.\n", func_num);
      }
      
      closedir(func);
    }
  }
  closedir(OUT);
  closedir(IN);
  
  printf("PASSED ALL TESTS $ $ $ $ $ $ $ $\n\n");
  
  return 0;
}
