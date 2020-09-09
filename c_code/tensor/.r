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
  uint64_t tiny_buffer = *(uint64_t *) &datum;  //dereferencing datum to remove type
  
  for(uint8_t i = 0; i < sizeof(ELEMENT); i++){ 
    buffer[*index + i] = 0;
    buffer[*index + i] += tiny_buffer;          //first byte of tiny_buffer is transferred to buffer
    tiny_buffer >>= 8;                          //loading next byte
  }

  *index+=sizeof(ELEMENT);
}

ELEMENT fish_ELEMENT(uint8_t *buffer, uint64_t *index){
  uint64_t tiny_buffer = 0; 
  
  for(uint8_t i = 0; i < sizeof(ELEMENT); i++){ 
    tiny_buffer <<= 8;                          //loading next byte  
    tiny_buffer += buffer[*index - i - 1];      //buffer is transferred to first byte of tiny_buffer
  }

  *index-=sizeof(ELEMENT);
  
  ELEMENT answer = *(ELEMENT *) &tiny_buffer;
  return answer;
}


void stream_FORM_LENGTH(FORM_LENGTH datum, uint8_t *buffer, uint64_t *index){
  uint64_t tiny_buffer = *(uint64_t *) &datum;  //dereferencing datum to remove type
  
  for(uint8_t i = 0; i < sizeof(FORM_LENGTH); i++){ 
    buffer[*index + i] = 0;
    buffer[*index + i] += tiny_buffer;          //first byte of tiny_buffer is transferred to buffer
    tiny_buffer >>= 8;                          //loading next byte
  }

  *index+=sizeof(FORM_LENGTH);
}

FORM_LENGTH fish_FORM_LENGTH(uint8_t *buffer, uint64_t *index){
  uint64_t tiny_buffer = 0; 
  
  for(uint8_t i = 0; i < sizeof(FORM_LENGTH); i++){ 
    tiny_buffer <<= 8;                          //loading next byte  
    tiny_buffer += buffer[*index - i - 1];      //buffer is transferred to first byte of tiny_buffer
  }

  *index-=sizeof(FORM_LENGTH);
  
  FORM_LENGTH answer = *(FORM_LENGTH *) &tiny_buffer;
  return answer;
}


void stream_FORM_ELEMENT(FORM_ELEMENT datum, uint8_t *buffer, uint64_t *index){
  uint64_t tiny_buffer = *(uint64_t *) &datum;  //dereferencing datum to remove type
  
  for(uint8_t i = 0; i < sizeof(FORM_ELEMENT); i++){ 
    buffer[*index + i] = 0;
    buffer[*index + i] += tiny_buffer;          //first byte of tiny_buffer is transferred to buffer
    tiny_buffer >>= 8;                          //loading next byte
  }

  *index+=sizeof(FORM_ELEMENT);
}

FORM_ELEMENT fish_FORM_ELEMENT(uint8_t *buffer, uint64_t *index){
  uint64_t tiny_buffer = 0; 
  
  for(uint8_t i = 0; i < sizeof(FORM_ELEMENT); i++){ 
    tiny_buffer <<= 8;                          //loading next byte  
    tiny_buffer += buffer[*index - i - 1];      //buffer is transferred to first byte of tiny_buffer
  }

  *index-=sizeof(FORM_ELEMENT);
  
  FORM_ELEMENT answer = *(FORM_ELEMENT *) &tiny_buffer;
  return answer;
}


void stream_DATA_LENGTH(DATA_LENGTH datum, uint8_t *buffer, uint64_t *index){
  uint64_t tiny_buffer = *(uint64_t *) &datum;  //dereferencing datum to remove type
  
  for(uint8_t i = 0; i < sizeof(DATA_LENGTH); i++){ 
    buffer[*index + i] = 0;
    buffer[*index + i] += tiny_buffer;          //first byte of tiny_buffer is transferred to buffer
    tiny_buffer >>= 8;                          //loading next byte
  }

  *index+=sizeof(DATA_LENGTH);
}

DATA_LENGTH fish_DATA_LENGTH(uint8_t *buffer, uint64_t *index){
  uint64_t tiny_buffer = 0; 
  
  for(uint8_t i = 0; i < sizeof(DATA_LENGTH); i++){ 
    tiny_buffer <<= 8;                          //loading next byte  
    tiny_buffer += buffer[*index - i - 1];      //buffer is transferred to first byte of tiny_buffer
  }

  *index-=sizeof(DATA_LENGTH);
  
  DATA_LENGTH answer = *(DATA_LENGTH *) &tiny_buffer;
  return answer;
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
  printf("OK nico, the time has arrived, a buffering test for you\n");
  uint8_t test[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  uint64_t index = 1;
  uint64_t index_save = index;
  uint64_t data = 0xfedcba9876543210;
  
  index_save = index;
  ELEMENT e = *(ELEMENT *) &data;
  printf("ELEMENT stream %08x\n", *(uint32_t *) &e);
  stream_ELEMENT(e, test, &index);
  printf("test ");
  for(int h = 0;h < 20; h++){
    printf("%02x", test[h]);
  }
  ELEMENT ef = fish_ELEMENT(test, &index);
  printf("\nELEMENT fish %08x\n",*(uint32_t *) &ef);
  printf("index %lu index before %lu\n\n",index,index_save);
  
  index = 6;
  index_save = index;
  FORM_LENGTH fl = *(FORM_LENGTH *) &data;
  printf("FORM_LENGTH stream %02x\n", *(uint8_t *) &fl);
  stream_FORM_LENGTH(fl, test, &index);
  printf("test ");
  for(int h = 0;h < 20; h++){
    printf("%02x", test[h]);
  }
  FORM_LENGTH fle = fish_FORM_LENGTH(test, &index);
  printf("\nFORM_LENGTH fish %02x\n",*(uint8_t *) &fle);
  printf("index %lu index before %lu\n\n",index,index_save);
  
  index = 8;
  index_save = index;
  FORM_ELEMENT fe = *(FORM_ELEMENT *) &data;
  printf("FORM_ELEMENT stream %08x\n", *(uint32_t *) &fe);
  stream_FORM_ELEMENT(fe, test, &index);
  printf("test ");
  for(int h = 0;h < 20; h++){
    printf("%02x", test[h]);
  }
  FORM_ELEMENT fef = fish_FORM_ELEMENT(test, &index);
  printf("\nFORM_ELEMENT fish %08x\n",*(uint32_t *) &fef);
  printf("index %lu index before %lu\n\n",index,index_save);
  
  index = 3;
  index_save = index;
  DATA_LENGTH dl = *(DATA_LENGTH *) &data;
  printf("DATA_LENGTH stream %08x\n", *(uint32_t *) &dl);
  stream_DATA_LENGTH(dl, test, &index);
  printf("test ");
  for(int h = 0;h < 20; h++){
    printf("%02x", test[h]);
  }
  DATA_LENGTH dlf = fish_DATA_LENGTH(test, &index);
  printf("\nDATA_LENGTH fish %08x\n",*(uint32_t *) &dlf);
  printf("index %lu index before %lu\n\n",index,index_save);
   
  return NULL;
}
