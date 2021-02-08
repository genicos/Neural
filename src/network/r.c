#include "network.h"

void save_NODES_LENGTH(IO *io, NODES_LENGTH datum){
  uint64_t buffer = *(uint64_t *)(&datum);
 
  switch (sizeof(NODES_LENGTH)){
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

NODES_LENGTH read_NODES_LENGTH(IO *io){
  uint64_t datum = 0;

  switch (sizeof(NODES_LENGTH)){
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

  return *(NODES_LENGTH *)(&datum);
}


void save_FUNCTION(IO *io, FUNCTION datum){
  uint64_t buffer = *(uint64_t *)(&datum);
 
  switch (sizeof(FUNCTION)){
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

FUNCTION read_FUNCTION(IO *io){
  uint64_t datum = 0;

  switch (sizeof(FUNCTION)){
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

  return *(FUNCTION *)(&datum);
}




bool network_save(char *file_name, network *w){
  if(!file_name || !w)
    return false;
  
  FILE *F = fopen(file_name, "w");
  if(!F)
    return false;
  
  IO *io = io_create(F);
  
  save_1_byte(io, typecode(NODES_LENGTH));
  save_1_byte(io, typecode(FUNCTION));
  
  save_1_byte(io, typecode(ELEMENT));
  save_1_byte(io, typecode(FORM_LENGTH));
  save_1_byte(io, typecode(FORM_ELEMENT));
  save_1_byte(io, typecode(DATA_LENGTH));
  
  
  if(!network_append(io, w)){
    io_delete(io);
    fclose(F);
    return false;
  }
  
  io_flush(io);
  io_delete(io);
  fclose(F); 
  
  return true;
}

bool network_append(IO *io, network *w){
  if(!io || !w)
    return false;

   
  save_NODES_LENGTH(io, w->nodes_length);
  save_NODES_LENGTH(io, w->root);
  
  for(NODES_LENGTH n = 0; n < w->nodes_length; n++){
    node *curr = w->nodes[n];
    
    save_1_byte(io, (uint8_t)((curr->t) != NULL));
    save_FUNCTION(io, curr->function);
    save_NODES_LENGTH(io, curr->parent_1);
    save_NODES_LENGTH(io, curr->parent_2);
    
    if(curr->t){
      if(!tensor_append(io, curr->t))
        return false;
    }
  }

  return true;
}


network *network_extrct(IO *io){
  if(!io)
    return NULL;
  
  NODES_LENGTH nodes_length = read_NODES_LENGTH(io);
  NODES_LENGTH root         = read_NODES_LENGTH(io);
  
  node **nodes = (node **)calloc(nodes_length, sizeof(node *));  
  
  for(NODES_LENGTH n = 0; n < nodes_length; n++){
    bool tensor_present = (read_1_byte(io) == 1);
    
    FUNCTION function = read_FUNCTION(io);
    NODES_LENGTH parent_1 = read_NODES_LENGTH(io);
    NODES_LENGTH parent_2 = read_NODES_LENGTH(io);
    
    tensor *t = NULL;

    if(tensor_present){
      t = tensor_extrct(io);
      if(!t){
        free(nodes);
        return NULL;
      }
    }
    
    nodes[n] = node_create(t, function, parent_1, parent_2);
    if(!nodes[n]){
      free(nodes);
      return NULL;
    }
    
    if(t)
      nodes[n]->tensor_responsibility = true;
    
  } 
  
  network *w = network_create(nodes_length, nodes);
  if(!w){
    free(nodes);
    return NULL;
  }
  free(nodes);
  w->nodes_responsibility = true; 
  w->root = root;
 

  return w;
}

network *network_read(char *file_name){
  if(!file_name)
    return NULL;

  FILE *F = fopen(file_name, "r");
  if(!F)
    return NULL;
  
  IO *io = io_create(F); 
  
  bool typematch = true;
  
  if(read_1_byte(io) != typecode(NODES_LENGTH))
    typematch = false;
  if(read_1_byte(io) != typecode(FUNCTION))
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

  network *w = network_extrct(io);
  
  io_delete(io);
  fclose(F);
   
  return w;
}
