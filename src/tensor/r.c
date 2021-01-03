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


void save_ELEMENT(FILE *F, ELEMENT datum){
  uint64_t buffer = *(uint64_t *)(&datum);

  for(uint8_t i = 0; i < sizeof(ELEMENT); i++){
    putc(buffer, F);
    buffer >>= 8;
  }
  
}

ELEMENT read_ELEMENT(FILE *F){
  uint64_t datum = 0;
  
  int c = 0;
  
  for(uint8_t i = 0; i < sizeof(ELEMENT); i++){
    if((c = getc(F)) == EOF)
      return 0;
    datum += (c << 8*i);
  }
  
  return *(ELEMENT *)(&datum);
}


void save_FORM_LENGTH(FILE *F, FORM_LENGTH datum){
  uint64_t buffer = *(uint64_t *)(&datum);

  for(uint8_t i = 0; i < sizeof(FORM_LENGTH); i++){
    putc(buffer, F);
    buffer >>= 8;
  }
  
}

FORM_LENGTH read_FORM_LENGTH(FILE *F){
  uint64_t datum = 0;
  
  int c = 0;
  
  for(uint8_t i = 0; i < sizeof(FORM_LENGTH); i++){
    if((c = getc(F)) == EOF)
      return 0;
    datum += (c << 8*i);
  }
  
  return *(FORM_LENGTH *)(&datum);
}


void save_FORM_ELEMENT(FILE *F, FORM_ELEMENT datum){
  uint64_t buffer = *(uint64_t *)(&datum);

  for(uint8_t i = 0; i < sizeof(FORM_ELEMENT); i++){
    putc(buffer, F);
    buffer >>= 8;
  }
  
}

FORM_ELEMENT read_FORM_ELEMENT(FILE *F){
  uint64_t datum = 0;
  
  int c = 0;
  
  for(uint8_t i = 0; i < sizeof(FORM_ELEMENT); i++){
    if((c = getc(F)) == EOF)
      return 0;
    datum += (c << 8*i);
  }
  
  return *(FORM_ELEMENT *)(&datum);
}


void save_DATA_LENGTH(FILE *F, DATA_LENGTH datum){
  uint64_t buffer = *(uint64_t *)(&datum);
  
  for(uint8_t i = 0; i < sizeof(DATA_LENGTH); i++){
    putc(buffer, F);
    buffer >>= 8;
  }
  
}

DATA_LENGTH read_DATA_LENGTH(FILE *F){
  uint64_t datum = 0;
  
  int c = 0;
  
  for(uint8_t i = 0; i < sizeof(DATA_LENGTH); i++){
    if((c = getc(F)) == EOF)
      return 0;
    datum += (c << 8*i);
  }
  
  return *(DATA_LENGTH *)(&datum);
}




bool tensor_save(char *file_name, tensor *t){
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
  
  save_FORM_LENGTH(F, t->form_length);
  
  for(FORM_LENGTH i = 0; i < t->form_length; i++){
    save_FORM_ELEMENT(F, t->form[i]);
  }
  
  for(DATA_LENGTH i = 0; i < t->data_length; i++){
    save_ELEMENT(F, t->data[i]); 
  }
  
  return true;
}

tensor *tensor_extrct(FILE *F){
  if(!F)
    return NULL;
  
  FORM_LENGTH form_length = read_FORM_LENGTH(F);
  
  FORM_ELEMENT *form = (FORM_ELEMENT *)malloc(form_length * sizeof(FORM_ELEMENT));
  if(!form)
    return NULL;
  
  for(FORM_LENGTH i = 0; i < form_length; i++){
    form[i] = read_FORM_ELEMENT(F);
  }

  tensor *t = tensor_create(form_length, form);
  free(form);
  if(!t)
    return NULL;
  
  if(!tensor_create_data(t))
    return NULL;

  for(DATA_LENGTH i = 0; i < t->data_length; i++){
    t->data[i] = read_ELEMENT(F);
  }
  
  return t;
}

tensor *tensor_read(char *file_name){
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
