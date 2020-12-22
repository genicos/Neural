#include "network.h"
#include <stdio.h>

void node_delete(node *n){
  if(n->tensor_responsibility){
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

bool node_equal(node *n, node *o){
  
  if(!n || !o)
    return false;
  
  if((n->t == NULL) ^ (o->t == NULL))
    return false;
  
  if(n->t)
    if(!tensor_equal(n->t, o->t))
     return false;
  
  if(n->function != o->function)
    return false;
  
  if(n->parent_1 != o->parent_1 || n->parent_2 != o->parent_2)
    return false;
  
  return true;
}


void network_delete(network *w){
  if(w){
    free(w->nodes);
    for(NODES_LENGTH i = 0; i < w->nodes_length; i++){
      tensor_delete(w->derivatives[i]);
    }
    free(w->derivatives);
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
    
    w->derivatives = (tensor **)calloc(nodes_length, sizeof(tensor *));
    if(!w->derivatives){
      return NULL;
    }
    
    for(NODES_LENGTH i = 0; i < nodes_length; i++){
      w->nodes[i] = nodes[i];
    }
  }
  
  w->nodes_length = nodes_length;

  return w;
}

bool network_equal(network *w, network *x){
  
  if(!w || !x)
    return false;
  
  if(w->nodes_length != x->nodes_length)
    return false;

  for(NODES_LENGTH i = 0; i < w->nodes_length; i++){
    if(!node_equal(w->nodes[i], x->nodes[i]))
      return false;
  }
  
  if(w->error != x->error)
    return false;
  
  return true;
}

void network_clean(network *w){
  for(NODES_LENGTH i = 0; i < w->nodes_length; i++){
    if(w->nodes[i] && w->nodes[i]->parent_1 != i && w->nodes[i]->t){
      tensor_delete(w->nodes[i]->t);
      w->nodes[i]->t = NULL;
      w->nodes[i]->tensor_responsibility = false;
    }
  }
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

    child->t = tensor_function_table[child->function]->create(parent_1->t, parent_2->t);
    if(!child->t){
      return false;
    }
    child->tensor_responsibility = true;
    
    tensor_function_table[child->function]->f(child->t, parent_1->t, parent_2->t);
    
    return true;
  }
  
  
  return false;
}


