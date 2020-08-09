#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

void printarray(double *arr, uint32_t length){
  for(uint32_t i = 0;i<length;i++){
    printf("%lf, ",arr[i]);
  }
}

int main(){
  
  uint32_t length = 10;
  
  double a[length];
  double b[length];
  
  for(uint32_t i = 0; i<length;i++){
    a[i] = (double)rand()/UINT32_MAX;
    b[i] = (double)rand()/UINT32_MAX;
  }
  
  printf("a: ");
  printarray(a,length);
  
  printf("\nb: ");
  printarray(b,length);
  
  double *addition = add(a,b,length);
  double dotproduct = dot(a,b,length);
  
  printf("\nsum: ");
  printarray(addition,length);

  printf("\ndot: %lf",dotproduct);
}
