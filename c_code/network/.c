#include ".h"
#include <stdio.h>

void node_delete(node *n){
  if(n && n->tensor_responsibility){
    tensor_delete(n->t);
  }
  free(n);
}

node *node_create(tensor *t, FUNCTION function, NODES_LENGTH parent_1, NODES_LENGTH parent_2){
  node *n = (node *)malloc(sizeof(node));
  if(!n){
    return NULL;
  }
  
  n->t = t;
  n->tensor_responsibility = false;

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
  
  node *child = w->nodes[n];

  if(child->t){
    if(child->t->data){    
      return true;
    }
    
    tensor_delete(child->t);
  }
  
  if(node_solve(w, child->parent_1) && node_solve(w, child->parent_2)){
    node *parent_1 = w->nodes[child->parent_1];
    node *parent_2 = w->nodes[child->parent_2];

    child->t = function_table(child->function, 3)(parent_1->t, parent_2->t, NULL);
    child->tensor_responsibility = true;
    
    function_table(child->function, 0)(child->t, parent_1->t, parent_2->t);
    
    return true;
  }
  
  
  return false;
}

tensor *node_partial_derivative(network *w, NODES_LENGTH n, NODES_LENGTH a){
  w+= n + n;
  return NULL;
}
