/* NETWORK

*/

#include <inttypes.h>
#include "../tensor/.h"

typedef NODES_LENGTH   uint8_t
typedef FUNCTION       uint8_t


typedef struct node{
  tensor *t;
  FUNCTION function;
  NODES_LENGTH parent_1;           //parents are indexes in network->nodes
  NODES_LENGTH parent_2;
} node;

typedef struct network{
  NODES_LENGTH nodes_length;
  node** nodes;
} network;

bool save_network(network *w, char *file_name);

network *read_network(char *file_name);



void node_delete(node *n);

node *node_create(tensor *t, FUNCTION function, NODES_LENGTH parent_1, NODES_LENGTH parent_2);

void network_delete(network *w);

network *network_create(NODES_LENGTH nodes_length,node *nodes);


//n is the node to solve:
bool node_solve(network *w, NODES_LENGTH n);

//returns partial derivative of n with respect to a
tensor *node_partial_derivative(network *w, NODES_LENGTH n, NODES_LENGTH a);
