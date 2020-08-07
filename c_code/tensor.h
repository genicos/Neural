/* TENSOR
 *  A TENSOR is structure of data.
 *
 *  A TENSOR is a container of ELEMENTS, with some orderings between the ELEMENTS.
 *  A TENSOR has a natural number, N, of orderings.
 *  The FORM of a tensor, is an ordered array of natural numbers greater than zero
 *    which determine the orderings between the elements
 *  The FORM has a length of N, each index of the FORM corrosponds to an ordering
 *    of the TENSOR
 *  The number J at index K of the FORM indicates the number of distinct values
 *    the ELEMENTS can have under ordering K within the TENSOR
 *
 *  
 *  Consider the following notation:
 *    X / O  This means that there is some order between X and O, denoted by /
 *    O \ X  This statement is equivalent to the above
 *    X /4 O There may be different orderings existing between X and O, so they
 *             are distinguished by a natural number
 *    X /-a O = X \a O 
 *  
 *  The following is true of the orderings of the elements of a TENSOR:
 *    a and b are integers
 *    
 *    (X /a O) ^ (O /a H) -> (X /a H)
 *      This is to say that all the orderings of a TENSOR are transative.
 *
 *    (X /a X)
 *      This is to say that all the orderings of a TENSOR are reflexive.
 *      This and the last fact imply that the orderings are partial orderings.
 *
 *    (a != b) ^ E(c): (X !=c O) -> !((X /a O) -> (X /b O))
 *      This is to say that knowledge of one ordering is independent of knowledge
 *      of another. Unless it is the same ordering. If b = -a, then two distict
 *      ELEMENTS cannot share the same directionality under both orderings, that is
 *      to say that no ordering is symmetric
 *
 *    E(X) ^ E(O) ^ E(a) ^ E(b) -> E(I): (X /a I) ^ (O /a I) ^ (X /b I) ^ (O /b I)
 *      This means that for every pair of ELEMENTS, and for every pair of orderings
 *      there exists an ELEMENT that is ordered beyond them in both orderings.
 *
 *    (X /a O) v (O /a X) 
 *      This means that every pair of ELEMENTS has some ordering under every ordering
 */
#ifndef NEURAL_C_CODE_TENSOR_H
#define NEURAL_C_CODE_TENSOR_H

#include <inttypes.h>
typedef float ELEMENT               //The type for the TENSOR ELEMENTS
typedef uint8_t FORM_LENGTH_STORE   //Size of FORM length type, for when a TENSOR is stored in a file
typedef uint32_t FORM_ELEMENT       //The type for the FORM ELEMENTS
typedef uint32_t DATA_LENGTH_STORE  //Size of DATA length type, for when a TENSOR is stored in a file

typedef struct tensor{
  FORM_LENGTH_STORE form_length;
  FORM_ELEMENT *form;
  
  DATA_LENGTH_STORE data_length;
  ELEMENT *data; //array of ELEMENTS
} tensor;

tensor* tensor_create(ELEMENT* data);

void tensor_delete(tensor *t);

tensor* tensor_add(tensor *A, tensor *B);

tensor* tensor_sub(tensor *A, tensor *B);

tensor* tensor_scale(tensor *A, ELEMENT c);



#endif NEURAL_C_CODE_TENSOR_H
