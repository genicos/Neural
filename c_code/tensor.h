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
 *    the ELEMENTS can have under ordering K within the TENSOR. 
 *    FORM[K] = J
 *  The COORDINATES of an ELEMENT are a list of N indicies, where the Kth index
 *    has FORM[K] number of possibilities, every ELEMENT in tensor has a unique
 *    COORDINATE. 
 *    C[M] is the ELEMENT in TENSOR C with COORDINATE M
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
typedef float ELEMENT;               //The type for the TENSOR ELEMENTS
typedef uint8_t FORM_LENGTH;         //Size of FORM length type

//size(FORM_ELEMENT) <= size(DATA_LENGTH_STORE), product of all FORM elements is equal to DATA length
typedef uint32_t FORM_ELEMENT;       //The type for the FORM ELEMENTS
typedef uint32_t DATA_LENGTH;        //Size of DATA length type
typedef DATA_LENGTH FORM_CASCADE_ELEMENT; //Element of form cascade


typedef struct tensor{
  FORM_LENGTH form_length;
  FORM_ELEMENT *form;
  FORM_CASCADE_ELEMENT *form_cascade; 
  
  DATA_LENGTH data_length;
  ELEMENT *data; //array of ELEMENTS
  //As the last index of form increases by 1, the index in data it corrosponds to increases by 1
} tensor;

tensor* tensor_create(FORM_ELEMENT *form, FORM_LENGTH form_length);

ELEMENT* tensor_create_data(tensor *t);

void tensor_delete_data(tensor *t);

void tensor_delete(tensor *t);

void tensor_print(tensor *t, char *printf_element_tag);



/*Adds two TENSORs
Inputs: pointers to TENSORs A and B to be added.
  A and B must have the same FORM.
Returns: pointer to TENSOR C.
  C has the same form as A and B.
  For any COORDINATE M,
    C[M] is equal to A[M] + B[M]
*/
tensor *tensor_add(tensor *C, tensor *A, tensor *B);

//Returns the partial derivative of C with respect to A
tensor *tensor_add_d_1(tensor *C, tensor *A, tensor *B);

//Returns the partial derivative of C with respect to B
tensor *tensor_add_d_2(tensor *C, tensor *A, tensor *B);

//Creates answer tensor to be used in function
tensor *tensor_add_create(tensor *A, tensor *B);

tensor *(*tensor_add_list[4])(tensor *, tensor *, tensor *) = {
  tensor_add,
  tensor_add_d_1,
  tensor_add_d_2,
  (tensor *(*)(tensor *, tensor *, tensor *)) tensor_add_create,
};

/*Subtracts two TENSORs
Inputs: pointers to TENSORs A and B to be subtracted.
  A and B must have the same FORM.
Returns: pointer to TENSOR C.
  C has the same form as A and B.
  For any COORDINATE M,
    C[M] is equal to A[M] - B[M]
*/
tensor *tensor_sub(tensor *C, tensor *A, tensor *B);

//Returns the partial derivative of C with respect to A
tensor *tensor_sub_d_1(tensor *C, tensor *A, tensor *B);

//Returns the partial derivative of C with respect to B
tensor *tensor_sub_d_2(tensor *C, tensor *A, tensor *B);

//Creates answer tensor to be used in function
tensor *tensor_sub_create(tensor *A, tensor *B);


/*Scales a TENSOR by a scalar ELEMENT
Inputs: pointer to TENSOR A to be scaled and ELEMENT B to be the scalar
Returns: pointer to TENSOR C.
  C has the same form as A.
  For any COORDINATE M,
    C[M] is equal to A[M] * B
*/
tensor *tensor_scale(tensor *C, tensor *A, tensor *B);

//Returns the partial derivative of C with respect to A
tensor *tensor_scale_d_1(tensor *C, tensor *A, tensor *B);

//Returns the partial derivative of C with respect to B
tensor *tensor_scale_d_2(tensor *C, tensor *A, tensor *B);

//Creates answer tensor to be used in function
tensor *tensor_scale_create(tensor *A, tensor *B);


/*Traditional fully connected layer
Inputs: pointers to TENSORs A and B, A is the activation layer and B is the parameter TENSOR
  FORM of A is ignored
  FORM[0] of B is to equal to A->length
Returns: pointer to TENSOR C
  FORM of C is equal to the FORM of B without the 0th index
  For any COORDINATE M,
    C[M] is equal to the sum of A[i]*B[{i,M}] as i increments
*/
tensor *tensor_full(tensor *C, tensor *A, tensor *B);

//Returns the partial derivative of C with respect to A
tensor *tensor_full_d_1(tensor *C, tensor *A, tensor *B);

//Returns the partial derivative of C with respect to B
tensor *tensor_full_d_2(tensor *C, tensor *A, tensor *B);

//Creates answer tensor to be used in function
tensor *tensor_full_create(tensor *A, tensor *B);

#endif
