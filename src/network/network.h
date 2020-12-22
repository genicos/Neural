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


//A leaf node is indicated by a node whose parent_1 is themselves
typedef struct node{
  tensor *t;
  bool tensor_responsibility;
  
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
  
  NODES_LENGTH error; //index of error node, usually is a scalar, ie has a form of {1}
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


//clears the data for all non-leaf nodes
void network_clean(network *w);

//n is the node to solve:
bool node_solve(network *w, NODES_LENGTH n);


#endif
