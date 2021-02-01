#include "lx.h"

void save_EXAMPLES_COUNT(FILE *F, EXAMPLES_COUNT datum){
  uint64_t buffer = *(uint64_t *)(&datum);
  
  for(uint8_t i = 0; i < sizeof(EXAMPLES_COUNT); i++){
    putc(buffer, F);
    buffer >>= 8;
  }
}

EXAMPLES_COUNT read_EXAMPLES_COUNT(FILE *F){
  uint64_t datum = 0;
  
  int c = 0;
  
  for(uint8_t i = 0; i < sizeof(EXAMPLES_COUNT); i++){
    if((c = getc(F)) == EOF)
      return 0;
    datum += (c << 8*i);
  }
  
  return *(EXAMPLES_COUNT *)(&datum);
}


void save_INPUTS_COUNT(FILE *F, INPUTS_COUNT datum){
  uint64_t buffer = *(uint64_t *)(&datum);
  
  for(uint8_t i = 0; i < sizeof(INPUTS_COUNT); i++){
    putc(buffer, F);
    buffer >>= 8;
  }
}

INPUTS_COUNT read_INPUTS_COUNT(FILE *F){
  uint64_t datum = 0;
  
  int c = 0;
  
  for(uint8_t i = 0; i < sizeof(INPUTS_COUNT); i++){
    if((c = getc(F)) == EOF)
      return 0;
    datum += (c << 8*i);
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
  
  
  if(!lx_append(F, x)){
    io_close(F);
    fclose(F);
    return false;
  }
  
  io_flush(io);
  io_close(io);
  fclose(F);
  
  return true;
}

bool lx_append(FILE *F, lx *x){// bad... i should start by converting tensor
  if(!F || !x)
    return false;
  
  save_EXAMPLES_COUNT(F, x->examples_count);
  save_INPUTS_COUNT(F, x->inputs_count);
    
  for(EXAMPLES_COUNT i = 0; i < x->examples_count*(x->inputs_count +1); i++){
    if(!tensor_append(F, x->examples[i]))
      return false;
  }
  
  return true;
}

lx *lx_extrct(FILE *F){
  if(!F)
    return NULL;
  
  lx *x = (lx *)calloc(1, sizeof(lx));
  if(!x)
    return NULL;
  
  x->examples_count = read_EXAMPLES_COUNT(F);
  x->inputs_count   = read_INPUTS_COUNT(F);
  
  x->examples = (tensor **)calloc(x->examples_count*(x->inputs_count +1), sizeof(tensor *));
  if(!x->examples){
    lx_delete(x);
    return NULL;
  }
  
  x->examples_responsibility = true;
  
  for(EXAMPLES_COUNT i = 0; i < x->examples_count*(x->inputs_count +1); i++){
    tensor *t = tensor_extrct(F);
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
  
  bool typematch = true;
  
  if(getc(F) != typecode(EXAMPLES_COUNT))
    typematch = false;
  if(getc(F) != typecode(INPUTS_COUNT))   
    typematch = false;
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
  
  lx *x = lx_extrct(F);
  
  fclose(F);
  
  return x;
}
