#include <stdio.h>
#include "tensor.h"

int main(){
  //Testing print_tensor
  uint32_t form[3] = {5,2,10};
  Tensor *a = tensor_create(3,form);
  
  ELEM data[100];
  for(int i = 0;i<100;i++){
    data[i] = (ELEM)rand()/UINT32_MAX;
  } 
  filldata(a,data);

  print_tensor(a);

  tensor_delete(a);
  //End of testing print_tensor
  
  //Testing fullyconnected
  uint32_t tempform[1] = {3};
  Tensor *fullyinput = tensor_create(1,tempform);

  ELEM tempdata[3] = { 1, 0.5, 0.25};
  filldata(fullyinput,tempdata);

  uint32_t wform[1] = {6};
  Tensor *weights = tensor_create(1,wform);

  ELEM wdata[6] = {1, 0, 1,  0, 1, 1};
  filldata(weights,wdata);

  Tensor *fullyoutput = fullyconnected(fullyinput, weights);
  printf("Should be 2: %lu\n", fullyoutput->length);
  
  print_tensor(fullyoutput);
  //End of testing fullyconnected
  
  //Testing convolution
  uint32_t imageform[2] = {2,4};
  Tensor *image = tensor_create(2,imageform);
  ELEM imagedata[8] = {0,1,0,1,
	                 0,1,0,1};
  filldata(image,imagedata);

  uint32_t filterform[2]= {2,2};
  Tensor *filter = tensor_create(2,filterform);
  ELEM filterdata[4] = {0,1,
	                  0,1};
  filldata(filter,filterdata);

  Tensor *convoluted = convolution(image,filter);
  print_tensor(convoluted);

  tensor_delete(image);
  tensor_delete(filter);
  tensor_delete(convoluted);

  tensor_delete(fullyinput);
  tensor_delete(weights);
  tensor_delete(fullyoutput);
  return 0;
}
