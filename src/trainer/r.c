#include "lx.h"

 void save_EXAMPLES_COUNT(IO *io, EXAMPLES_COUNT datum){
  uint64_t buffer = *(uint64_t *)(&datum);
  
  switch (sizeof(EXAMPLES_COUNT)){
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

EXAMPLES_COUNT read_EXAMPLES_COUNT(IO *io){
  uint64_t datum = 0;
  
  switch (sizeof(EXAMPLES_COUNT)){
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
 
  return *(EXAMPLES_COUNT *)(&datum);
}


void save_INPUTS_COUNT(IO *io, INPUTS_COUNT datum){
  uint64_t buffer = *(uint64_t *)(&datum);
  
  switch (sizeof(INPUTS_COUNT)){
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

INPUTS_COUNT read_INPUTS_COUNT(IO *io){
  uint64_t datum = 0;
  
  switch (sizeof(INPUTS_COUNT)){
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
 
  return *(INPUTS_COUNT *)(&datum);
}




bool lx_save(char *file_name, lx *x){
  if(!file_name || !x)
    return false;
  
  FILE *F = fopen(file_name, "w");
  if(!F)
    return false;
  
  IO *io = io_create(F);
  
  save_1_byte(io, typecode(EXAMPLES_COUNT));
  save_1_byte(io, typecode(INPUTS_COUNT));

  save_1_byte(io, typecode(ELEMENT));
  save_1_byte(io, typecode(FORM_LENGTH));
  save_1_byte(io, typecode(FORM_ELEMENT));
  save_1_byte(io, typecode(DATA_LENGTH));
  
  
  if(!lx_append(io, x)){
    io_delete(io);
    fclose(F);
    return false;
  }
  
  io_flush(io);
  io_delete(io);
  fclose(F);
  
  return true;
}

bool lx_append(IO *io, lx *x){
  if(!io || !x)
    return false;
  
  save_EXAMPLES_COUNT(io, x->examples_count);
  save_INPUTS_COUNT(io, x->inputs_count);
    
  for(EXAMPLES_COUNT i = 0; i < x->examples_count*(x->inputs_count +1); i++){
    if(!tensor_append(io, x->examples[i]))
      return false;
  }
  
  return true;
}

lx *lx_extrct(IO *io){
  if(!io)
    return NULL;
  
  lx *x = (lx *)calloc(1, sizeof(lx));
  if(!x)
    return NULL;
  
  x->examples_count = read_EXAMPLES_COUNT(io);
  x->inputs_count   = read_INPUTS_COUNT(io);
  
  x->examples = (tensor **)calloc(x->examples_count*(x->inputs_count +1), sizeof(tensor *));
  if(!x->examples){
    lx_delete(x);
    return NULL;
  }
  
  x->examples_responsibility = true;
  
  for(EXAMPLES_COUNT i = 0; i < x->examples_count*(x->inputs_count +1); i++){
    tensor *t = tensor_extrct(io);
    if(!t){
      lx_delete(x);
      return NULL;
    }
    x->examples[i] = t;
  }
  
  return x;
}

lx *lx_read(char *file_name){
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
  
  if(read_1_byte(io) != typecode(EXAMPLES_COUNT))
    typematch = false;
  if(read_1_byte(io) != typecode(INPUTS_COUNT))   
    typematch = false;
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
  
  lx *x = lx_extrct(io);
  
  io_delete(io);
  fclose(F);
  
  return x;
}
