#include ".h"
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

/*
type table
bit/s  meaning
-----  -------
1      0 - int, 1 - floating point
2      0 - unsigned, 1 - signed
3-8    size

type     bcode     dcode
------------------------
uint8_t  00000100  4
uint16_t 00001000  8
uint32_t 00010000  16
uint64_t 00100000  32 
int8_t   00000110  6 
int16_t  00001010  10
int32_t  00010010  18
int64_t  00100010  34
float    00010011  19
double   00100011  35
*/

#define typecode(t)  (uint8_t)(isfloat(t) + (issigned(t) << 1) + (sizeof(t) << 2))


void stream_ELEMENT(ELEMENT datum, uint8_t *buffer, uint64_t *index){
  uint64_t tiny_buffer = *(uint64_t *) &datum;
  printf("A %lx\n",tiny_buffer);
   
  //uint8_t shift = (sizeof(ELEMENT) - 1) * 8;
  for(uint8_t i = 0; i < sizeof(ELEMENT); i++){
    buffer[*index + i] += tiny_buffer;
    printf("A %lx %x\n",tiny_buffer, buffer[*index + i]);
    tiny_buffer >>= 8;
  }
  *index+=sizeof(ELEMENT);
}

bool tensor_write(tensor *t, char *file_name){
  if(!t){
    return false;
  }
  
  FILE *file = fopen(file_name, "w");
  
  uint64_t file_size = 0;
  file_size += 4;                   //type codes for ELEMENT, FORM_LENGTH, FORM_ELEMENT, DATA_LENGTH
  file_size += sizeof(FORM_LENGTH); //form length
  file_size += sizeof(FORM_ELEMENT) * t->form_length; //form
  file_size += sizeof(ELEMENT) * t->data_length;      //data

  uint8_t *buffer = (uint8_t *)calloc(file_size, 1);
  if(!buffer){
    return false;
  }
  
  return true;
}

tensor *tensor_read(){
  printf(":AS\n");
  uint8_t test[10] = {0,0,0,0,0,0,0,0,0,0};
  uint64_t index = 1;
   
  for(int h = 0;h < 10; h++){
    printf("S%x \n", test[h]);
  }

  uint32_t di = 0xAABBCCDD;
  ELEMENT d = * (ELEMENT *) &di;
  
  stream_ELEMENT(d, test, &index);
  
  for(int h = 0;h < 10; h++){
    printf("F%x \n", test[h]);
  }
  printf("wow %lu", index);
  return NULL;
}
