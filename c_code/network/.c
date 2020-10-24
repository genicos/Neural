#include ".h"

void node_delete(node *n){
  free(n);
}

node *node_create(tensor *t, FUNCTION function, NODES_LENGTH parent_1, NODES_LENGTH parent_2){
  node *n = (node *)malloc(sizeof(node));
  if(!n){
    return NULL;
  }
  
  n->t = t;
  
  n->function = function;

  n->parent_1 = parent_1;
  n->parent_2 = parent_2; 
  
  return n;
}


void network_delete(network *w){
  if(w){
    free(w->nodes);
  }
  free(w);
}

network *network_create(NODES_LENGTH nodes_length, node **nodes){
  if(nodes_length && !nodes){
    return NULL;
  }
  
  network *w = (network *) malloc(sizeof(network));
  if(!w){
    return NULL;
  }
  
  if(nodes_length){
    w->nodes = (node **) malloc(nodes_length * sizeof(node *));
    if(!w->nodes){
      return NULL;
    }
    
    for(NODES_LENGTH i = 0; i < nodes_length; i++){
      w->nodes[i] = nodes[i];
    }
  }
  
  w->nodes_length = nodes_length;

  return w;
}



bool node_solve(network *w, NODES_LENGTH n){
  if(!w){
    return false;
  }
  
  if(n >= w->nodes_length){
    return false;
  }
  
  node *curr = w->nodes[n];

  if(curr->t->data){
    return true;
  }
  
  //
  //
  //
  return false;
  
}

tensor *node_partial_derivative(network *w, NODES_LENGTH n, NODES_LENGTH a){
  w+= n + n;
  return NULL;
}
