#include ".h"
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
  t->form[0] = form[0];//index of for loop below will not reach 0
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

ELEMENT* tensor_create_data(tensor *t){
  if(!t){
    return NULL;
  }
  t->data = (ELEMENT *)calloc(t->data_length, sizeof(ELEMENT));
  return t->data;
}


void tensor_print(tensor *t, char* printf_element_tag){
  if(!t){
    printf("Null tensor\n");
    return; 
  }
  
  for(FORM_LENGTH b = 0; b < t->form_length; b++){
    putchar('{');
  }
  
  char *datum_string = (char *)calloc(7,1);
  sprintf(datum_string, " %%%s,",printf_element_tag);
  
  for(DATA_LENGTH i = 0; i < t->data_length; i++){
    if(i>0){
      FORM_LENGTH brackets = 0;
      
      for(FORM_LENGTH fi = 0; fi < t->form_length; fi++){
        if(i % t->form_cascade[fi] == 0){
          brackets++;
        }
      }
      
      for(FORM_LENGTH b = 0; b < brackets; b++){
        putchar('}');
      }
      if(brackets > 0){
        putchar('\n');
      }
      for(FORM_LENGTH b = 0; b < brackets; b++){
        putchar('{');
      }
    }
    
    printf(datum_string, t->data[i]);
  }
  
  free(datum_string);
  
  for(FORM_LENGTH b = 0; b < t->form_length; b++){
    putchar('}');
  }
   
  putchar('\n');
}



tensor* tensor_add(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i] + B->data[i];
  
  return C;
}

tensor* tensor_add_d_1(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = 1;
  
  return C;
}

tensor* tensor_add_d_2(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = 1;
  
  return C;
}

tensor* tensor_add_create(tensor *A, tensor *B){
  tensor *C = tensor_create(A->form, A->form_length);
  tensor_create_data(C);
  
  return C;
}

//tensor *(*tensor_add_table[4])(tensor *, tensor *, tensor *) = {
//  tensor_add,
//  tensor_add_d_1,
//  tensor_add_d_2,
//  (tensor *(*)(tensor *, tensor *, tensor *)) tensor_add_create,
//};




tensor* tensor_sub(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i] - B->data[i];
  
  return C;
}

tensor* tensor_sub_d_1(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = 1;
  
  return C;
}

tensor* tensor_sub_d_2(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = -1;
  
  return C;
}

tensor* tensor_sub_create(tensor *A, tensor *B){
  tensor *C = tensor_create(A->form, A->form_length);
  tensor_create_data(C);
  
  return C;
}



tensor* tensor_scale(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i] * B->data[0];
  
  return C;
}

tensor* tensor_scale_d_1(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = B->data[0];
  
  return C;
}

tensor* tensor_scale_d_2(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < A->data_length; i++)
    C->data[i] = A->data[i];
  
  return C;
}

tensor* tensor_scale_create(tensor *A, tensor *B){
  tensor *C = tensor_create(A->form, A->form_length);
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
  
  for(DATA_LENGTH i = 0; i < C->data_length; i++){
    for(DATA_LENGTH h = 0; h < A->data_length; h++){
      C->data[i] += B->data[i + (h * C->data_length)];
    }
  }

  return C;
}

tensor* tensor_full_d_2(tensor *C, tensor *A, tensor *B){
  
  for(DATA_LENGTH i = 0; i < C->data_length; i++){
    for(DATA_LENGTH h = 0; h < A->data_length; h++){
      C->data[i] += A->data[h];
    }
  }

  return C;
}

tensor* tensor_full_create(tensor *A, tensor *B){
  tensor *C = tensor_create(&B->form[1], B->form_length-1);
  tensor_create_data(C);
  
  return C;
}