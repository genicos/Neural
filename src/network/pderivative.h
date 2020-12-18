#ifndef PDERIVATIVE_H
#define PDERIVATIVE_H

#include "../project.h"
#include "network.h"

typedef struct pderivative_tree{
  NODES_LENGTH lineage_count;
  uint8_t **lineages;
  //array of pointers, each pointer points to an array of ints, either 1 or 2,
  // indicating the parent
  bool lineages_responsibility;

//or i might store node indexi
} pderivative_tree;


void delete_pdtree(pderivative_tree *t);

pderivative_tree *create_pdtree(NODES_LENGTH depth);


void add_ancestor(pderivative_tree *t, uint8_t parent, NODES_LENGTH depth);

//Does not preserve input data
pderivative_tree *conjoin_trees(pderivative_tree *of_parent_1, pderivative_tree *of_parent_2);


pderivative_tree *partial_derivative(network *w, NODES_LENGTH derivative_of, NODES_LENGTH with_respect_to, NODES_LENGTH curr, NODES_LENGTH depth);




bool propogate_error(network *w, NODES_LENGTH *parameters);

bool back_propogate(network *w, NODES_LENGTH *parameters, node *curr, tensor *derv);

#endif
