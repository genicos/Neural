#include "pderivative.h"
#include <stdio.h>

void delete_pdtree(pderivative_tree *t){
  if(t->lineages_responsibility && t->lineages){
    for(int i = 0; i < t->lineage_count; i++){
      free(t->lineages[i]);
    }
    free(t->lineages);
  }
  free(t);
}

pderivative_tree *create_pdtree(NODES_LENGTH depth){
  pderivative_tree *t = (pderivative_tree *)calloc(1, sizeof(pderivative_tree));
  if(!t){
    return NULL;
  }
  t->lineages = (uint8_t **)calloc(1,sizeof(uint8_t *));
  if(!t->lineages){
    delete_pdtree(t);
    return NULL;
  }
  t->lineages[0] = (uint8_t *)calloc(depth+1, 1);
  if(!t->lineages[0]){
    delete_pdtree(t);
    return NULL;
  }
  
  t->lineages_responsibility = true;
  t->lineage_count = 1;
  
  return t;
}

void add_ancestor(pderivative_tree *t, uint8_t parent, NODES_LENGTH depth){
  if(!t){
    return;
  }
  for(NODES_LENGTH i = 0; i < t->lineage_count; i++){
    t->lineages[i][depth] = parent;
  }
}

pderivative_tree *conjoin_trees(pderivative_tree *a, pderivative_tree *b){
  if(!a || !b){
    if(a)
      return a;
    else
      return b; 
  }
  NODES_LENGTH new_lineage_count = a->lineage_count + b->lineage_count;
  a->lineages = (uint8_t **)realloc(a->lineages, new_lineage_count*sizeof(uint8_t *));
  for(NODES_LENGTH i = 0; i < b->lineage_count; i++){
    a->lineages[a->lineage_count + i] = b->lineages[i];
  }
  free(b->lineages);
  b->lineages_responsibility = false; //a inherited lineages from b
  a->lineage_count = new_lineage_count;
  delete_pdtree(b);
  return a;
}


pderivative_tree *partial_derivative(network *w, NODES_LENGTH derivative_of, NODES_LENGTH with_respect_to, NODES_LENGTH curr, NODES_LENGTH depth){
  if(!w){
    return NULL;
  }
  
  if(curr == with_respect_to){
    return create_pdtree(depth); //Fruit
  }
  
  node *curr_node = w->nodes[curr];
  
  NODES_LENGTH parent_1 = curr_node->parent_1;
  NODES_LENGTH parent_2 = curr_node->parent_2;
  
  if(curr == parent_1 && curr == parent_2){ //Orphan node
    return NULL; //Dead end
  }


  pderivative_tree *from_parent_1 = NULL, *from_parent_2 = NULL;
  
  if(curr != parent_1){    //recursively looking for the node with_respect_to 
    from_parent_1 = partial_derivative(w, derivative_of, with_respect_to, parent_1, depth+1);
    add_ancestor(from_parent_1, 1, depth);
  }
  if(curr != parent_2){
    from_parent_2 = partial_derivative(w, derivative_of, with_respect_to, parent_2, depth+1);
    add_ancestor(from_parent_2, 2, depth);
  }
  
  
  
  if(from_parent_1){
    curr_node->pderivative_1 = tensor_cartesian_product(curr_node->t, w->nodes[parent_1]->t);
    curr_node->pderivative_1_responsibility = true;
    
    if(curr_node->pderivative_1){
      tensor_function_table[curr_node->function]->
        f_d_1(curr_node->pderivative_1, w->nodes[parent_1]->t, w->nodes[parent_2]->t);
    }
  }
  
  if(from_parent_2){
    curr_node->pderivative_2 = tensor_cartesian_product(curr_node->t, w->nodes[parent_2]->t);
    curr_node->pderivative_2_responsibility = true;
    
    if(curr_node->pderivative_2){
      tensor_function_table[curr_node->function]->
        f_d_2(curr_node->pderivative_2, w->nodes[parent_1]->t, w->nodes[parent_2]->t);
    }
  }
  
  
  return conjoin_trees(from_parent_1, from_parent_2);
}



bool propogate_error(network *w, NODES_LENGTH *prameters){
  
  node *error;
  
  if(!(error = w->nodes[w->error])){
    return false;
  }
  
  node *parent_1, *parent_2;
  
  if((parent_1 = w->nodes[error->parent_1]) != error){
    
  }

  if((parent_2 = w->nodes[error->parent_2]) != error){
  
  }

  return false;
}

bool back_propogate(network *w, NODES_LENGTH *parameters, node *curr, tensor *derv){
  return false;
}
