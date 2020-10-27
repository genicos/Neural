/* NETWORK

*/

#include <inttypes.h>
#include "../tensor/.h"
#include "../project.h"

typedef uint8_t NODES_LENGTH;
typedef uint8_t FUNCTION;


typedef struct node{
  tensor *t;
  bool tensor_responsibility;
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
