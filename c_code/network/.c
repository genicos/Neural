#include ".h"

void node_delete(node *n){
  if(n){
    free(n->t);
    free(n->parents);
  }
  free(n);
}

node *node_create(tensor *t, PARENTS_LENGTH parents_length, NODES_LENGTH *parents){
  if(parents_length && !parents){
    return NULL;
  }

  node *n = (node *)malloc(sizeof(node));
  
}
