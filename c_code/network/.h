/* NETWORK

*/

#include <inttypes.h>
#include "../tensor/.h"

typedef PARENTS_LENGTH uint8_t
typedef NODES_LENGTH   uint8_t
typedef FUNCTION       uint8_t


typedef struct node{
  tensor *t;
  FUNCTION function;
  PARENTS_LENGTH parents_length;
  NODES_LENGTH *parents;           //array of indexes in network->nodes
} node;

typedef struct network{
  NODES_LENGTH nodes_length;
  node* nodes;
} network;

bool save_network(network *w, char *file_name);

network *read_network(char *file_name);



void node_delete(node *n);

node *node_create(tensor *t, PARENTS_LENGTH parents_length, tensor **parents);

void network_delete(network *w);

network *network_create(NODES_LENGTH nodes_length,node *nodes);



bool node_solve(network *w, NODES_LENGTH n);

//returns partial derivative of n with respect to a
tensor *node_partial_derivative(network *w, NODES_LENGTH n, NODES_LENGTH a);
