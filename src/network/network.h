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





void         save_NODES_LENGTH(FILE *F, NODES_LENGTH datum);
NODES_LENGTH read_NODES_LENGTH(FILE *F);

void         save_FUNCTION    (FILE *F, FUNCTION datum);
FUNCTION     read_FUNCTION    (FILE *F);




//network byte representation
//
//  typecode is defined in project.h
//  so() means sizeof()
//
//  bytes              meaning        representation
//  ------------------------------------------------
//  1                  NODES_LENGTH   typecode        \
//  1                  FUNCTION       typecode        |
//  1                  ELEMENT        typecode        |--preamble
//  1                  FORM_LENGTH    typecode        |
//  1                  FORM_ELEMENT   typecode        |
//  1                  DATA_LENGTH    typecode        /
//  so(NODES_LENGTH)   nodes_length   NODES_LENGTH
//  so(NODES_LENGTH)   error          NODES_LENGTH
//  indeterminate      nodes          nodes_length # of node representations
//  
//
//  node byte representation
//  
//  bytes              meaning        representation
//  ------------------------------------------------
//  1                  tensor exists  0 for false, 1 for true
//  so(FUNCTION)       function       FUNCTION
//  so(NODES_LENGTH)   parent_1       NODES_LENGTH
//  so(NODES_LENGTH)   parent_2       NODES_LENGTH
//  indeterminate      tensor         tensor representation without preamble
//
bool     network_save(char *file_name, network *w);  //Creates file, appends network to it, closes file
bool     network_append(FILE *F, network *w);        //Append network to file
network *network_extrct(FILE *F);                    //Extract next network from file
network *network_read(char *file_name);              //Opens file, extracts network, closes file



//destructor for node
//
// `n: node to be deleted
void node_delete(node *n);

//constructor for node
//
// `t: tensor held by node. `t may be NULL, in which case the tensor will be calculated
//     by applying the binary tensor function `function to (`parent_1, `parent_2)
// `function: binary tensor function which would be applied to (`parent_1,`parent_2) to
//     result in `t 
// `parent_1:  first argument passed to `function to give `t, expressed as an index for some networks `nodes
// `parent_2: second argument passed to `function to give `t, expressed as an index for some networks `nodes
//
// `node_create: container for `t, `function, `parent_1, `parent_2
node *node_create(tensor *t, FUNCTION function, NODES_LENGTH parent_1, NODES_LENGTH parent_2);

//determines if two nodes are equal
//
//Two nodes are equal if:
//  Their tensors are equal
//  They have the same `function
//  They have the same `parent_1 and `parent_2
// 
// `n:  first node to be compared
// `o: second node to be compared
//
// `node_equal: true if `n and `o are equal, false if they are not
bool node_equal(node *n, node *o);

//destructor for network
//
// `w: network to be deleted
void network_delete(network *w);

//constructor for network
//
// `nodes_length: length of `nodes
// `nodes: array of pointers to nodes of the network
//
// `network_create: container for `nodes array, along with an index for the error tensor
//     and an array of tensors 
network *network_create(NODES_LENGTH nodes_length,node **nodes);


//clears the data for the tensors of all non-leaf nodes, and the derivatives array
//
// `w: network to be cleaned
void network_clean(network *w);

//calculates a node from a network
//
// `w: network containing node
// `n: index of node in `w->nodes
bool node_solve(network *w, NODES_LENGTH n);

//determines if two networks are equal
//
//Two networks are equal if:
//  They have the same `nodes_length
//  For each index of `nodes:
//    the two nodes pointed to are equal
//  They have the same `error
//
// `w:  first network to be compared
// `x: second network to be compared
//
// `network_equal: true if `w and `x are equal, and false if they are not
bool network_equal(network *w, network *x);
#endif
