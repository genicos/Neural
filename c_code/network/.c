#include ".h"
#include <stdio.h>

void node_delete(node *n){
  if(n->tensor_responsibility){
    tensor_delete(n->t);
  }
  if(n->pderivative_1_responsibility){
    tensor_delete(n->pderivative_1);
  }
  if(n->pderivative_2_responsibility){
    tensor_delete(n->pderivative_2);
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

  n->pderivative_1 = NULL;
  n->pderivative_1_responsibility = false;

  n->pderivative_2 = NULL;
  n->pderivative_2_responsibility = false;
  
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





tensor *node_partial_derivative(network *w, NODES_LENGTH n, NODES_LENGTH a){
  if(!w || !w->nodes){
    return NULL;
  }
  
  if(!node_solve(w, n)){
    return NULL;
  }
  //this is gonna be complicated
  return NULL;
}
