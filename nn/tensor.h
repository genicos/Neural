#ifndef __TENSOR_H__
#define __TENSOR_H__


#include "vector.h"
#include <stdlib.h>
#include <stdbool.h>

//Tensor structure
//
////////////////////////////////////////////////////////////////////////////////////////
                                                                                      //
typedef float ELEM;        //elements of tensor                                       //
                                                                                      //
typedef struct Tensor{                                                                //
  uint8_t dimensions;      //length of form and formcascade, the order of the tensor  //
  uint32_t *form;          //size of each dimension                                   //
  uint64_t *formcascade;   //running product of form,                                 //
  //form[dimensions-1] = formcascade[dimensions-1]                                    //
  //formcascade[n-1] = form[n-1]*formcascade[n]                                       //
                                                                                      //
  uint64_t length;         //length of data (product of every form number)            //
  ELEM *data;              //data                                                     //
} Tensor;                                                                             //
                                                                                      //
Tensor *tensor_create(uint8_t dimensions, uint32_t *form);                            //
                                                                                      //
void tensor_delete(Tensor *t);                                                        //
                                                                                      //
void filldata(Tensor *t, ELEM *originaldata);                                         //
                                                                                      //
void print_tensor(Tensor *t);                                                         //
                                                                                      //
////////////////////////////////////////////////////////////////////////////////////////




//function codes are stored in 1 byte
//
//0, fully connected
//1, max pool
//2, convolution
//3, softmax
//4, PReLU
//5, pair wise add
//6, pair wise multiply
extern uint8_t f_players[256];//number of tensors involved in an operation, including inputs, outputs, and parameters.





Tensor *convolution(Tensor *image, Tensor *filter);

Tensor *fullyconnected(Tensor *input, Tensor *weights);



typedef struct s_access{
  ELEM *(*f)   (ELEM *,ELEM *);
  ELEM *(*dfdx)(ELEM *,ELEM *);
  bool pairwise_independent;
} s_access;

//Name of function, note on parameter
//  definition of function
//////////////////////////////////////////////////////
//function                                          //
//                                                  //
//derivative of function                            //
//                                                  //
//structure containing pointers to above functions, //
//and a bool pairwise_independent.                  //
//  this is true if F[i] only depends on in[i]      //
//////////////////////////////////////////////////////


//Prelu, takes a single parameter: the slope in the negative input region
//  Prelu(x) = if x<0  : param[0] * x;
//             if x>=0 : x;
// 
//////////////////////////////////////////////////////////////////
ELEM *fprelu(ELEM *in, ELEM *parameters);    //function   //
                                                   //and        //
ELEM *dprelu_dx(ELEM *in, ELEM *parameters); //derivative //
                                                                //
                                //                              //
//////////////////////////////////////////////////////////////////


//Softmax, takes no parameters
//  Softmax(x[i]) = exp(x[i])
//                      /
//                 Sum(j,exp(x[j]))
// 
//////////////////////////////////////////////////////////////////////
ELEM *fsoftmax(ELEM *in, ELEM *parameters);    //function     //
                                                     //and          //
ELEM *dsoftmax_dx(ELEM *in, ELEM *parameters); //derivative   //
                                                                    //
                                //                                 //
//////////////////////////////////////////////////////////////////////




#endif
