#include "tensor.h"
#include "../io.h"
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


void save_ELEMENT(IO *io, ELEMENT datum){
  uint64_t buffer = *(uint64_t *)(&datum);
  
  switch (sizeof(ELEMENT)){
    case 1:
      save_1_byte(io, (uint8_t)buffer);
    break;
    case 2:
      save_2_byte(io, (uint16_t)buffer);
    break;
    case 4:
      save_4_byte(io, (uint32_t)buffer);
    break;
    case 8:
      save_8_byte(io, (uint64_t)buffer);
    break;
  }
}

ELEMENT read_ELEMENT(IO *io){
  uint64_t datum = 0;
  
  switch (sizeof(ELEMENT)){
    case 1:
      datum = read_1_byte(io);
    break;
    case 2:
      datum = read_2_byte(io);
    break;
    case 4:
      datum = read_4_byte(io);
    break;
    case 8:
      datum = read_8_byte(io);
    break;
  }
  
  return *(ELEMENT *)(&datum);
}


void save_FORM_LENGTH(IO *io, FORM_LENGTH datum){
  uint64_t buffer = *(uint64_t *)(&datum);
  
  switch (sizeof(FORM_LENGTH)){
    case 1:
      save_1_byte(io, (uint8_t)buffer);
    break;
    case 2:
      save_2_byte(io, (uint16_t)buffer);
    break;
    case 4:
      save_4_byte(io, (uint32_t)buffer);
    break;
    case 8:
      save_8_byte(io, (uint64_t)buffer);
    break;
  }
}

FORM_LENGTH read_FORM_LENGTH(IO *io){
  uint64_t datum = 0;
  
  switch (sizeof(FORM_LENGTH)){
    case 1:
      datum = read_1_byte(io);
    break;
    case 2:
      datum = read_2_byte(io);
    break;
    case 4:
      datum = read_4_byte(io);
    break;
    case 8:
      datum = read_8_byte(io);
    break;
  }
  
  return *(FORM_LENGTH *)(&datum);
}


void save_FORM_ELEMENT(IO *io, FORM_ELEMENT datum){
  uint64_t buffer = *(uint64_t *)(&datum);
  
  switch (sizeof(FORM_ELEMENT)){
    case 1:
      save_1_byte(io, (uint8_t)buffer);
    break;
    case 2:
      save_2_byte(io, (uint16_t)buffer);
    break;
    case 4:
      save_4_byte(io, (uint32_t)buffer);
    break;
    case 8:
      save_8_byte(io, (uint64_t)buffer);
    break;
  }
}

FORM_ELEMENT read_FORM_ELEMENT(IO *io){
  uint64_t datum = 0;
  
  switch (sizeof(FORM_ELEMENT)){
    case 1:
      datum = read_1_byte(io);
    break;
    case 2:
      datum = read_2_byte(io);
    break;
    case 4:
      datum = read_4_byte(io);
    break;
    case 8:
      datum = read_8_byte(io);
    break;
  }
  
  return *(FORM_ELEMENT *)(&datum);
}


void save_DATA_LENGTH(IO *io, DATA_LENGTH datum){
  uint64_t buffer = *(uint64_t *)(&datum);
  
  switch (sizeof(DATA_LENGTH)){
    case 1:
      save_1_byte(io, (uint8_t)buffer);
    break;
    case 2:
      save_2_byte(io, (uint16_t)buffer);
    break;
    case 4:
      save_4_byte(io, (uint32_t)buffer);
    break;
    case 8:
      save_8_byte(io, (uint64_t)buffer);
    break;
  }
}

DATA_LENGTH read_DATA_LENGTH(IO *io){
  uint64_t datum = 0;
  
  switch (sizeof(DATA_LENGTH)){
    case 1:
      datum = read_1_byte(io);
    break;
    case 2:
      datum = read_2_byte(io);
    break;
    case 4:
      datum = read_4_byte(io);
    break;
    case 8:
      datum = read_8_byte(io);
    break;
  }
  
  return *(DATA_LENGTH *)(&datum);
}






bool tensor_save(char *file_name, tensor *t){
  if(!file_name || !t)
    return false;
  
  FILE *F = fopen(file_name, "w");
  if(!F)
    return false;
  
  IO *io = io_create(F);
  if(!io)
    return false;
  
  save_1_byte(io, typecode(ELEMENT));
  save_1_byte(io, typecode(FORM_LENGTH));
  save_1_byte(io, typecode(FORM_ELEMENT));
  save_1_byte(io, typecode(DATA_LENGTH));
  
  
  if(!tensor_append(io, t)){
    io_delete(io);
    fclose(F);
    return false;
  }
  
  io_flush(io);
  io_delete(io);
  fclose(F);
  

  return true;
}

bool tensor_append(IO *io, tensor *t){
  if(!io || !t)
    return false;
  
  save_FORM_LENGTH(io, t->form_length);
  
  for(FORM_LENGTH i = 0; i < t->form_length; i++){
    save_FORM_ELEMENT(io, t->form[i]);
  }
  
  for(DATA_LENGTH i = 0; i < t->data_length; i++){
    save_ELEMENT(io, t->data[i]); 
  }
  
  return true;
}

tensor *tensor_extrct(IO *io){
  if(!io)
    return NULL;
  
  FORM_LENGTH form_length = read_FORM_LENGTH(io);
  
  FORM_ELEMENT *form = (FORM_ELEMENT *)malloc(form_length * sizeof(FORM_ELEMENT));
  if(!form)
    return NULL;
  
  for(FORM_LENGTH i = 0; i < form_length; i++){
    form[i] = read_FORM_ELEMENT(io);
  }

  tensor *t = tensor_create(form_length, form);
  free(form);
  if(!t)
    return NULL;
  
  if(!tensor_create_data(t)){
    tensor_delete(t);
    return NULL;
  }

  for(DATA_LENGTH i = 0; i < t->data_length; i++){
    t->data[i] = read_ELEMENT(io);
  }
  
  return t;
}

tensor *tensor_read(char *file_name){
  if(!file_name)
    return NULL;
  
  FILE *F = fopen(file_name, "r");
  if(!F)
    return NULL;
  
  IO *io = io_create(F);
  if(!io){
    fclose(F);
    return NULL;
  }
  
  bool typematch = true;
  
  if(read_1_byte(io) != typecode(ELEMENT))
    typematch = false;
  if(read_1_byte(io) != typecode(FORM_LENGTH))
    typematch = false;
  if(read_1_byte(io) != typecode(FORM_ELEMENT))
    typematch = false;
  if(read_1_byte(io) != typecode(DATA_LENGTH))
    typematch = false;
  
  if(!typematch){
    io_delete(io);
    fclose(F);
    return NULL;
  }
  
  tensor *t = tensor_extrct(io);
  
  io_delete(io);
  fclose(F);
   
  return t;
}
