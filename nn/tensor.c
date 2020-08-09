#include "tensor.h"

#include <stdlib.h>
#include <stdio.h>

void tensor_delete(Tensor *t){
  if(t){
    free(t->form);
    free(t->formcascade);
    free(t->data);
    free(t);
  }
}

Tensor *tensor_create(uint8_t dimensions, uint32_t *form){
  if(!form || dimensions == 0){
    return NULL;
  }

  Tensor *fresh = (Tensor *)malloc(sizeof(Tensor));
  if(!fresh){
    return NULL;
  }

  fresh->dimensions = dimensions;
  fresh->form = (uint32_t *)calloc(dimensions, sizeof(uint32_t));
  if(!fresh->form){
    tensor_delete(fresh);
    return NULL;
  }
  
  fresh->formcascade = (uint64_t *)calloc(dimensions, sizeof(uint64_t));
  if(!fresh->formcascade){
    tensor_delete(fresh);
    return NULL;
  }

  fresh->formcascade[dimensions-1] = form[dimensions-1];
  fresh->form[0] = form[0];
  for(uint8_t d = dimensions-1; d > 0; d--){
    fresh->form[d] = form[d];
    
    if(form[d-1] > UINT64_MAX/fresh->formcascade[d]){
      tensor_delete(fresh);
      return NULL;
    } 

    fresh->formcascade[d-1] = fresh->formcascade[d] * form[d-1];
  }

  if(fresh->formcascade[0] == 0){
    tensor_delete(fresh);
    return NULL;
  }
  
  fresh->length = fresh->formcascade[0];
  fresh->data = (ELEM *)calloc(fresh->length, sizeof(ELEM));
  if(!fresh->data){
    tensor_delete(fresh);
    return NULL;
  }

  return fresh;
}

void filldata(Tensor *t, ELEM *originaldata){
  if(t){
    for(uint64_t i = 0; i < t->length; i++){
      t->data[i] = originaldata[i];
    }
  }
}

void print_tensor(Tensor *t){
  if(!t){
    printf("Null tensor\n");
    return;
  }
  
  
  for(uint8_t d = 0; d < t->dimensions; d++){ 
    printf("{");
  }
  
  for(uint64_t i = 0; i< t->length; i++){//printing data
    if(i>0){
      uint8_t resonant = 0;
      for(uint8_t d = 0; d < t->dimensions; d++){
	if(i % t->formcascade[d] == 0){//determining number of brakets needed
	  resonant++;
	}
      }
            
      for(uint8_t d = 0; d<resonant; d++){
        printf("}");
      }
      if(resonant>0){
        printf("\n");
      }
      for(uint8_t d = 0; d<resonant; d++){
        printf("{");
      }
    }
    printf(" %lf,",t->data[i]);
  }
  
  for(uint8_t d = 0; d < t->dimensions ;d++){
    printf("}");
  }
  
  printf("\n");
  
}

uint8_t f_players[256] = {
3,
2,
3,
2,
3,
3,
3,
};


//filter should have an equal number of dimensions as image
//  if filter has more dimensions, extra dimensions are ignored
//  if filter has less dimensions, missing dimensions are treated as 1
//Each dimensions of filter must not exceed the corrosponding dimension of image
Tensor *convolution(Tensor *image, Tensor *filter){
   
  uint32_t *ans_form = (uint32_t *)calloc(image->dimensions ,sizeof(uint32_t));
  if(!ans_form){
    return NULL;
  }
   
  
  //d is dimension in image
  for(uint8_t d = 0 ; d < image->dimensions ; d++){
    
    uint32_t image_d_size = image->form[d];
    uint32_t filter_d_size = (d < filter->dimensions) ? filter->form[d] : 1;
    
    if(filter_d_size > image_d_size){
      free(ans_form);
      return NULL;
    }
    
    ans_form[d] = image_d_size - filter_d_size + 1;  
  }

  Tensor *ans = tensor_create(image->dimensions, ans_form);
  free(ans_form);

  if(!ans){
    return NULL;
  }

  
  // formcascade[d]/form[d] is distance between data in dimension d 
  for(uint64_t i = 0; i < ans->length; i++){
    for(uint64_t j = 0;j < filter->length; j++){
      
      uint64_t image_element = 0;
      for(uint8_t d = 0; d < image->dimensions; d++){
	uint64_t filter_index_in_dim_d = (j / (filter->formcascade[d]/filter->form[d])) % (filter->form[d]);
       	uint64_t ans_index_in_dim_d    = (i / (   ans->formcascade[d]/   ans->form[d])) % (   ans->form[d]);
        image_element += (filter_index_in_dim_d + ans_index_in_dim_d) * (image->formcascade[d]/image->form[d]);
      }

      ans->data[i] += filter->data[j] * image->data[image_element];
    }
  }

  return ans;
}


//weights are organized with input index as small index
Tensor *fullyconnected(Tensor *input, Tensor *weights){
  if(weights->length % input->length != 0){
    return NULL;
  }
  
  uint32_t form[1] = {weights->length / input->length};
  Tensor *ans = tensor_create(1,form);
  if(!ans){
    return NULL;
  }
  
  ELEM *data = (ELEM *)calloc(ans->length , sizeof(ELEM));
  for(uint64_t i = 0; i < weights->length; i++){
    data[i / input->length] += weights->data[i] * input->data[i % input->length]; 
  }
  filldata(ans,data);
  free(data);
  return ans;
}



ELEM *fprelu(ELEM *in, ELEM *parameters){
  ELEM *ans =(ELEM *)calloc(1,sizeof(ELEM));
  if(in[0]<0){
    ans[0] = parameters[0] * in[0];
  }else{
    ans[0] = in[0];
  }
  return ans;
}

ELEM *dprelu_dx(ELEM *in, ELEM *parameters){
  in++;
  return parameters;
}











ELEM *fsoftmax(ELEM *in, ELEM *parameters){
  in++;
  return parameters;
}

ELEM * dsoftmax_dx(ELEM *in, ELEM *parameters){
  in++;
  return parameters;
}

struct s_access s_softmax;
  //s_softmax.f = &fsoftmax;
  //s_softmax.df_dx = &dsoftmax_dx;
  //s_softmax.pairwise_independent = false;



