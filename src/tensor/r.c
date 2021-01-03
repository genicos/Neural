#include "tensor.h"
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


void newsave_ELEMENT(FILE *F, ELEMENT datum){
  uint64_t buffer = *(uint64_t *)(&datum);

  for(uint8_t i = 0; i < sizeof(ELEMENT); i++){
    putc(buffer, F);
    buffer >>= 8;
  }
  
}

ELEMENT newread_ELEMENT(FILE *F){
  uint64_t datum = 0;
  
  int c = 0;
  
  for(uint8_t i = 0; i < sizeof(ELEMENT); i++){
    if((c = getc(F)) == EOF)
      return 0;
    datum += (c << 8*i);
  }
  
  return *(ELEMENT *)(&datum);
}


void newsave_FORM_LENGTH(FILE *F, FORM_LENGTH datum){
  uint64_t buffer = *(uint64_t *)(&datum);

  for(uint8_t i = 0; i < sizeof(FORM_LENGTH); i++){
    putc(buffer, F);
    buffer >>= 8;
  }
  
}

FORM_LENGTH newread_FORM_LENGTH(FILE *F){
  uint64_t datum = 0;
  
  int c = 0;
  
  for(uint8_t i = 0; i < sizeof(FORM_LENGTH); i++){
    if((c = getc(F)) == EOF)
      return 0;
    datum += (c << 8*i);
  }
  
  return *(FORM_LENGTH *)(&datum);
}


void newsave_FORM_ELEMENT(FILE *F, FORM_ELEMENT datum){
  uint64_t buffer = *(uint64_t *)(&datum);

  for(uint8_t i = 0; i < sizeof(FORM_ELEMENT); i++){
    putc(buffer, F);
    buffer >>= 8;
  }
  
}

FORM_ELEMENT newread_FORM_ELEMENT(FILE *F){
  uint64_t datum = 0;
  
  int c = 0;
  
  for(uint8_t i = 0; i < sizeof(FORM_ELEMENT); i++){
    if((c = getc(F)) == EOF)
      return 0;
    datum += (c << 8*i);
  }
  
  return *(FORM_ELEMENT *)(&datum);
}


void newsave_DATA_LENGTH(FILE *F, DATA_LENGTH datum){
  uint64_t buffer = *(uint64_t *)(&datum);
  
  for(uint8_t i = 0; i < sizeof(DATA_LENGTH); i++){
    putc(buffer, F);
    buffer >>= 8;
  }
  
}

DATA_LENGTH newread_DATA_LENGTH(FILE *F){
  uint64_t datum = 0;
  
  int c = 0;
  
  for(uint8_t i = 0; i < sizeof(DATA_LENGTH); i++){
    if((c = getc(F)) == EOF)
      return 0;
    datum += (c << 8*i);
  }
  
  return *(DATA_LENGTH *)(&datum);
}








void save_ELEMENT(uint8_t *buffer, uint64_t *index, ELEMENT datum){
  uint64_t tiny_buffer = *(uint64_t *) &datum;  //dereferencing datum to remove type
  
  for(uint8_t i = 0; i < sizeof(ELEMENT); i++){ 
    buffer[*index + i] = 0;
    buffer[*index + i] += tiny_buffer;          //first byte of tiny_buffer is transferred to buffer
    tiny_buffer >>= 8;                          //loading next byte
  }

  *index+=sizeof(ELEMENT);
}

ELEMENT read_ELEMENT(uint8_t *buffer, uint64_t *index){
  uint64_t tiny_buffer = 0; 
  
  *index+=sizeof(ELEMENT);
  
  for(uint8_t i = 0; i < sizeof(ELEMENT); i++){ 
    tiny_buffer <<= 8;                          //loading next byte  
    tiny_buffer += buffer[*index - i - 1];      //buffer is transferred to first byte of tiny_buffer
  }

  *index+=0;
  
  ELEMENT answer = *(ELEMENT *) &tiny_buffer;
  return answer;
}


void save_FORM_LENGTH(uint8_t *buffer, uint64_t *index, FORM_LENGTH datum){
  uint64_t tiny_buffer = *(uint64_t *) &datum;  //dereferencing datum to remove type
  
  for(uint8_t i = 0; i < sizeof(FORM_LENGTH); i++){ 
    buffer[*index + i] = 0;
    buffer[*index + i] += tiny_buffer;          //first byte of tiny_buffer is transferred to buffer
    tiny_buffer >>= 8;                          //loading next byte
  }

  *index+=sizeof(FORM_LENGTH);
}


FORM_LENGTH read_FORM_LENGTH(uint8_t *buffer, uint64_t *index){
  uint64_t tiny_buffer = 0; 
  
  *index+=sizeof(FORM_LENGTH);
  
  for(uint8_t i = 0; i < sizeof(FORM_LENGTH); i++){ 
    tiny_buffer <<= 8;                          //loading next byte  
    tiny_buffer += buffer[*index - i - 1];      //buffer is transferred to first byte of tiny_buffer
  }

  
  FORM_LENGTH answer = *(FORM_LENGTH *) &tiny_buffer;
  return answer;
}


void save_FORM_ELEMENT(uint8_t *buffer, uint64_t *index, FORM_ELEMENT datum){
  uint64_t tiny_buffer = *(uint64_t *) &datum;  //dereferencing datum to remove type
  
  for(uint8_t i = 0; i < sizeof(FORM_ELEMENT); i++){ 
    buffer[*index + i] = 0;
    buffer[*index + i] += tiny_buffer;          //first byte of tiny_buffer is transferred to buffer
    tiny_buffer >>= 8;                          //loading next byte
  }

  *index+=sizeof(FORM_ELEMENT);
}

FORM_ELEMENT read_FORM_ELEMENT(uint8_t *buffer, uint64_t *index){
  uint64_t tiny_buffer = 0; 
  
  *index+=sizeof(FORM_ELEMENT);
  
  for(uint8_t i = 0; i < sizeof(FORM_ELEMENT); i++){ 
    tiny_buffer <<= 8;                          //loading next byte  
    tiny_buffer += buffer[*index - i - 1];      //buffer is transferred to first byte of tiny_buffer
  }

  
  FORM_ELEMENT answer = *(FORM_ELEMENT *) &tiny_buffer;
  return answer;
}


void save_DATA_LENGTH(uint8_t *buffer, uint64_t *index, DATA_LENGTH datum){
  uint64_t tiny_buffer = *(uint64_t *) &datum;  //dereferencing datum to remove type
  
  for(uint8_t i = 0; i < sizeof(DATA_LENGTH); i++){ 
    buffer[*index + i] = 0;
    buffer[*index + i] += tiny_buffer;          //first byte of tiny_buffer is transferred to buffer
    tiny_buffer >>= 8;                          //loading next byte
  }

  *index+=sizeof(DATA_LENGTH);
}

DATA_LENGTH read_DATA_LENGTH(uint8_t *buffer, uint64_t *index){
  uint64_t tiny_buffer = 0; 
  
  *index+=sizeof(DATA_LENGTH);
  
  for(uint8_t i = 0; i < sizeof(DATA_LENGTH); i++){ 
    tiny_buffer <<= 8;                          //loading next byte  
    tiny_buffer += buffer[*index - i - 1];      //buffer is transferred to first byte of tiny_buffer
  }

  
  DATA_LENGTH answer = *(DATA_LENGTH *) &tiny_buffer;
  return answer;
}



bool tensor_save(char *file_name, tensor *t){
  if(!t || !file_name){
    return false;
  }
  
  FILE *file = fopen(file_name, "w");
  
  uint64_t file_size = 0;
  file_size += 4;                                     //type codes for ELEMENT, FORM_LENGTH, FORM_ELEMENT, DATA_LENGTH
  file_size += sizeof(FORM_LENGTH);                   //form length
  file_size += sizeof(FORM_ELEMENT) * t->form_length; //form
  file_size += sizeof(ELEMENT) * t->data_length;      //data

  uint8_t *buffer = (uint8_t *)calloc(file_size, 1);
  if(!buffer){
    return false;
  }
  uint64_t index = 0;

  buffer[index++] = typecode(ELEMENT);
  buffer[index++] = typecode(FORM_LENGTH); 
  buffer[index++] = typecode(FORM_ELEMENT); 
  buffer[index++] = typecode(DATA_LENGTH);
  
  save_FORM_LENGTH(buffer, &index, t->form_length);
  for(FORM_LENGTH i = 0; i < t->form_length; i++){
    save_FORM_ELEMENT(buffer, &index, t->form[i]);
  }
  for(DATA_LENGTH i = 0; i < t->data_length; i++){
    save_ELEMENT(buffer, &index, t->data[i]);
  }
  
  fwrite(buffer, 1, file_size, file);
  free(buffer);
  if(fclose(file)!=0){
    return false;
  }
  
  return true;
}



tensor *tensor_read(char *file_name){
  if(!file_name)
    return NULL;
  
  
  FILE *file = fopen(file_name, "r");
  
  if(!file)
    return NULL;
  
  fseek(file, 0L, SEEK_END);
  uint64_t file_size = ftell(file);
  fseek(file, 0L, SEEK_SET);
  
  if(file_size < 4 + sizeof(FORM_LENGTH)) //Check if type data is in file
    return NULL;
  
  uint8_t *buffer = (uint8_t *)calloc(file_size, 1);
  uint64_t index = 0;
  
  fread(buffer, 1, file_size, file);
  fclose(file);
  
  bool type_match = true;
  if(buffer[index++] != typecode(ELEMENT))
    type_match = false;
  if(buffer[index++] != typecode(FORM_LENGTH))
    type_match = false;
  if(buffer[index++] != typecode(FORM_ELEMENT))
    type_match = false;
  if(buffer[index++] != typecode(DATA_LENGTH))
    type_match = false;
  
  if(!type_match)
    return NULL;
  
  FORM_LENGTH form_length = read_FORM_LENGTH(buffer, &index);
  
  FORM_ELEMENT *form = (FORM_ELEMENT *)malloc(form_length * sizeof(FORM_ELEMENT));
  
  if(file_size - index < form_length*sizeof(FORM_ELEMENT))
    return NULL;
  
  for(FORM_LENGTH i = 0; i < form_length; i++){
    form[i] = read_FORM_ELEMENT(buffer, &index);
  }
  
  tensor *t = tensor_create(form_length, form);
  free(form);
  
  if(!tensor_create_data(t))
    return NULL;
  
  for(DATA_LENGTH i = 0; i < t->data_length; i++){
    t->data[i] = read_ELEMENT(buffer, &index);
  }
  
  free(buffer);
  
  
  return t;
}



bool newtensor_save(char *file_name, tensor *t){
  if(!file_name || !t)
    return false;
  
  FILE *F = fopen(file_name, "w");
  if(!F)
    return false;
  
  putc(typecode(ELEMENT),      F);
  putc(typecode(FORM_LENGTH),  F);
  putc(typecode(FORM_ELEMENT), F);
  putc(typecode(DATA_LENGTH),  F);

  if(!tensor_append(F, t))
    return false;
  
  fclose(F);
  
  return true;
}

bool tensor_append(FILE *F, tensor *t){
  if(!F || !t)
    return false;
  
  newsave_FORM_LENGTH(F, t->form_length);
  
  for(FORM_LENGTH i = 0; i < t->form_length; i++){
    newsave_FORM_ELEMENT(F, t->form[i]);
  }
  
  for(DATA_LENGTH i = 0; i < t->data_length; i++){
    newsave_ELEMENT(F, t->data[i]); 
  }
  
  return true;
}

tensor *tensor_extrct(FILE *F){
  if(!F)
    return NULL;
  
  FORM_LENGTH form_length = newread_FORM_LENGTH(F);
  
  FORM_ELEMENT *form = (FORM_ELEMENT *)malloc(form_length * sizeof(FORM_ELEMENT));
  if(!form)
    return NULL;
  
  for(FORM_LENGTH i = 0; i < form_length; i++){
    form[i] = newread_FORM_ELEMENT(F);
  }

  tensor *t = tensor_create(form_length, form);
  free(form);
  if(!t)
    return NULL;
  
  if(!tensor_create_data(t))
    return NULL;

  for(DATA_LENGTH i = 0; i < t->data_length; i++){
    t->data[i] = newread_ELEMENT(F);
  }
  
  return t;
}

tensor *newtensor_read(char *file_name){
  if(!file_name)
    return NULL;
  
  FILE *F = fopen(file_name, "r");
  if(!F)
    return NULL;
  
  bool typematch = true;
  
  if(getc(F) != typecode(ELEMENT))
    typematch = false;
  if(getc(F) != typecode(FORM_LENGTH))
    typematch = false;
  if(getc(F) != typecode(FORM_ELEMENT))
    typematch = false;
  if(getc(F) != typecode(DATA_LENGTH))
    typematch = false;
  
  if(!typematch){
    fclose(F);
    return NULL;
  }
  
  tensor *t = tensor_extrct(F);
  
  fclose(F);
  
  if(!t){
    return NULL;
  }
   
  return t;
}
