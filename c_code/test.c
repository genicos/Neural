#include "project.h"
#include <inttypes.h>
#include <stdio.h>

int main(){
  printf("max of uint8_t:%llu \n", maxof(uint8_t));
  printf("max of uint16_t:%llu \n", maxof(uint16_t));
  printf("max of uint32_t:%llu \n", maxof(uint32_t));
  printf("max of uint64_t:%llu \n", maxof(uint64_t));
  printf("max of int8_t:%llu \n", maxof(int8_t));
  printf("max of int16_t:%llu \n", maxof(int16_t));
  printf("max of int32_t:%llu \n", maxof(int32_t));
  printf("max of int64_t:%llu \n", maxof(int64_t));
  
  
  
  
  return 0; 
}
