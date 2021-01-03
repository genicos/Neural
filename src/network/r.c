#include "network.h"

void save_NODES_LENGTH(FILE *F, NODES_LENGTH datum){
  uint64_t buffer = *(uint64_t *)(&datum);
  
  for(uint8_t i = 0; i < sizeof(NODES_LENGTH); i++){
    putc(buffer, F);
    buffer >>= 8;
  }
}

NODES_LENGTH read_NODES_LENGTH(FILE *F){
  uint64_t datum = 0;
  
  int c = 0;

  for(uint8_t i = 0; i < sizeof(NODES_LENGTH); i++){
    if((c = getc(F)) == EOF)
      return 0;
    datum += (c << 8*i);
  } 

  return *(NODES_LENGTH *)(&datum); 
}


void save_FUNCTION(FILE *F, FUNCTION datum){
  uint64_t buffer = *(uint64_t *)(&datum);
  
  for(uint8_t i = 0; i < sizeof(FUNCTION); i++){
    putc(buffer, F);
    buffer >>= 8;
  }
}

FUNCTION read_FUNCTION(FILE *F){
  uint64_t datum = 0;
  
  int c = 0;

  for(uint8_t i = 0; i < sizeof(FUNCTION); i++){
    if((c = getc(F)) == EOF)
      return 0;
    datum += (c << 8*i);
  } 

  return *(FUNCTION *)(&datum); 
}




bool network_save(char *file_name, network *w){
  if(!file_name || !w)
    return false;
  
  FILE *F = fopen(file_name, "w");
  if(!F)
    return false;
  
  putc(typecode(NODES_LENGTH), F);
  putc(typecode(FUNCTION), F);
  
  putc(typecode(ELEMENT), F);
  putc(typecode(FORM_LENGTH), F);
  putc(typecode(FORM_ELEMENT), F);
  putc(typecode(DATA_LENGTH), F);
  
  if(!network_append(F, w))
    return false;
  
  fclose(F);
   
  return false;
}

bool network_append(FILE *F, network *w){
  if(!F || !w)
    return false;
   
  save_NODES_LENGTH(F, w->nodes_length);
  save_NODES_LENGTH(F, w->error);
  
  for(NODES_LENGTH n = 0; n < w->nodes_length; n++){
    node *curr = w->nodes[n];
    
    putc((int)((curr->t) != NULL), F);
    save_FUNCTION(F, curr->function);
    save_NODES_LENGTH(F, curr->parent_1);
    save_NODES_LENGTH(F, curr->parent_2);
    
    if(curr->t){
      if(!tensor_append(F, curr->t))
        return false;
    }
  }
  
  return true;
}


network *network_extrct(FILE *F){
  if(!F)
    return NULL;
  
  NODES_LENGTH nodes_length = read_NODES_LENGTH(F);
  NODES_LENGTH error        = read_NODES_LENGTH(F);
  
  node **nodes = (node **)calloc(nodes_length, sizeof(node *));  
  
  for(NODES_LENGTH n = 0; n < nodes_length; n++){
    bool tensor_present = (getc(F) == 1);
    
    FUNCTION function = read_FUNCTION(F);
    NODES_LENGTH parent_1 = read_NODES_LENGTH(F);
    NODES_LENGTH parent_2 = read_NODES_LENGTH(F);
    
    tensor *t = NULL;

    if(tensor_present){
      t = tensor_extrct(F);
      if(!t)
        return NULL;
    }
    
    nodes[n] = node_create(t, function, parent_1, parent_2);
    if(!nodes[n])
      return NULL;
    
  } 
  
  network *w = network_create(nodes_length, nodes);
  if(!w)
    return NULL;
  
  w->error = error;
  
  return w;
}

network *network_read(char *file_name){
  if(!file_name)
    return NULL;
  
  FILE *F = fopen(file_name, "r");
  if(!F)
    return NULL;
  
  bool typematch = true;
  
  if(getc(F) != typecode(NODES_LENGTH))
    typematch = false;
  if(getc(F) != typecode(FUNCTION))
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

  network *w = network_extrct(F);
  
  fclose(F);
   
  return w;
}
