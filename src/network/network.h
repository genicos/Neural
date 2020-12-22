/* NETWORK

*/
#ifndef NETWORK_H
#define NETWORK_H


#include <inttypes.h>
#include "../tensor/tensor.h"
#include "../tensor/functions.h"
#include "../project.h"

typedef uint8_t NODES_LENGTH;
typedef uint8_t FUNCTION;


typedef struct node{
  tensor *t;
  bool tensor_responsibility;
  
  tensor *pderivative_1;
  bool pderivative_1_responsibility;
  
  tensor *pderivative_2;
  bool pderivative_2_responsibility;
  
  FUNCTION function;
  NODES_LENGTH parent_1;           //parents are indexes in network->nodes
  NODES_LENGTH parent_2;
} node;

//no cycles may exists in the network
//Only leaf nodes may have more that one parent
//network is responsible for node array, but not for nodes
typedef struct network{
  NODES_LENGTH nodes_length;
  node** nodes;
  
  node* error; //usually is a scalar, ie has a form of {1}
  tensor** derivatives; //The partial derivatives of error with respect to
    //the other nodes, calculated as needed. 
} network;

bool save_network(network *w, char *file_name);

network *read_network(char *file_name);


//written
void node_delete(node *n);

//written
node *node_create(tensor *t, FUNCTION function, NODES_LENGTH parent_1, NODES_LENGTH parent_2);

//written
void network_delete(network *w);

//written
network *network_create(NODES_LENGTH nodes_length,node **nodes);


//clears the data for all nodes whos parents are not themselves
void network_clean(network *w);

//n is the node to solve:
bool node_solve(network *w, NODES_LENGTH n);

//returns partial derivative of n with respect to a
tensor *node_partial_derivative(network *w, NODES_LENGTH n, NODES_LENGTH a);

#endif
