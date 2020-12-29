/* TENSOR
 *  A TENSOR is a structure of data.
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

#include "../project.h"

typedef float       ELEMENT;              //The type for the TENSOR ELEMENTS
typedef uint8_t     FORM_LENGTH;          //Size of FORM length type
//size(FORM_ELEMENT) <= size(DATA_LENGTH), product of all FORM elements is equal to DATA length
typedef uint32_t    FORM_ELEMENT;         //The type for the FORM ELEMENTS
typedef uint32_t    DATA_LENGTH;          //Size of DATA length type
typedef DATA_LENGTH FORM_CASCADE_ELEMENT; //Element of form cascade


typedef struct tensor{
  FORM_LENGTH           form_length;
  FORM_ELEMENT         *form;
  FORM_CASCADE_ELEMENT *form_cascade; 
  
  DATA_LENGTH           data_length;
  ELEMENT              *data; //array of ELEMENTS
  //As the last index of form increases by 1, the index in data it corrosponds to increases by 1
  bool                  data_responsibility; //Marked true when data was created by tensor function, if true: tensor_delete will free data as well
} tensor;



void         save_ELEMENT     (uint8_t *buffer, uint64_t *index, ELEMENT datum);
ELEMENT      read_ELEMENT     (uint8_t *buffer, uint64_t *index);

void         save_FORM_LENGTH (uint8_t *buffer, uint64_t *index, FORM_LENGTH datum);
FORM_LENGTH  read_FORM_LENGTH (uint8_t *buffer, uint64_t *index);

void         save_FORM_ELEMENT(uint8_t *buffer, uint64_t *index, FORM_ELEMENT datum);
FORM_ELEMENT read_FORM_ELEMENT(uint8_t *buffer, uint64_t *index);

void         save_DATA_LENGTH (uint8_t *buffer, uint64_t *index, DATA_LENGTH datum);
DATA_LENGTH  read_DATA_LENGTH (uint8_t *buffer, uint64_t *index);


bool    tensor_save(char *file_name, tensor *t);
tensor *tensor_read(char *file_name);


void         newsave_ELEMENT     (uint8_t *buffer, uint64_t *index, ELEMENT datum);
ELEMENT      newread_ELEMENT     (uint8_t *buffer, uint64_t *index);

void         newsave_FORM_LENGTH (uint8_t *buffer, uint64_t *index, FORM_LENGTH datum);
FORM_LENGTH  newread_FORM_LENGTH (uint8_t *buffer, uint64_t *index);

void         newsave_FORM_ELEMENT(uint8_t *buffer, uint64_t *index, FORM_ELEMENT datum);
FORM_ELEMENT newread_FORM_ELEMENT(uint8_t *buffer, uint64_t *index);

void         newsave_DATA_LENGTH (uint8_t *buffer, uint64_t *index, DATA_LENGTH datum);
DATA_LENGTH  newread_DATA_LENGTH (uint8_t *buffer, uint64_t *index);


bool    newtensor_save(char *file_name, tensor *t);
tensor *newtensor_read(char *file_name);



//Creates a tensor without data
tensor* tensor_create(FORM_LENGTH form_length, FORM_ELEMENT *form);

//Allocates memory for tensor data
//memory is initialized to zero
ELEMENT* tensor_create_data(tensor *t);

void tensor_delete(tensor *t);

void tensor_print(tensor *t, char *printf_element_tag);

//returns true if
//both tensors are non-null,
//they have the same form_length,
//they have the same form element values, and
//they have the same data element values
bool tensor_equal(tensor *A, tensor *B);

//Creates a tensor with form {A->data_length, B->data_length}
//tensor *tensor_cartesian_product(tensor *A, tensor *B);
//
//
//
/////////////////////////////////////////////
///for all partial derivative functions
//the answer tensor has to be made with
//tensor_cartesian_product
/////////////////////////////////////////////

/*Adds two TENSORs
Inputs: pointers to TENSORs A and B to be added.
  A and B must have the same FORM.
Returns: pointer to TENSOR C.
  C has the same form as A and B.
  For any COORDINATE M,
    C[M] is equal to A[M] + B[M]

tensor *tensor_add(tensor *C, tensor *A, tensor *B);

//Returns the partial with respect to A, and places it into C
tensor *tensor_add_d_1(tensor *C, tensor *A, tensor *B);

//Returns the partial with respect to B, and places it into C
tensor *tensor_add_d_2(tensor *C, tensor *A, tensor *B);

//Creates answer tensor to be used in function
tensor *tensor_add_create(tensor *A, tensor *B);



Subtracts two TENSORs
Inputs: pointers to TENSORs A and B to be subtracted.
  A and B must have the same FORM.
Returns: pointer to TENSOR C.
  C has the same form as A and B.
  For any COORDINATE M,
    C[M] is equal to A[M] - B[M]

tensor *tensor_sub(tensor *C, tensor *A, tensor *B);

//Returns the partial with respect to A, and places it into C
tensor *tensor_sub_d_1(tensor *C, tensor *A, tensor *B);

//Returns the partial with respect to B, and places it into C
tensor *tensor_sub_d_2(tensor *C, tensor *A, tensor *B);

//Creates answer tensor to be used in function
tensor *tensor_sub_create(tensor *A, tensor *B);


Scales a TENSOR by a scalar ELEMENT
Inputs: pointer to TENSOR A to be scaled and ELEMENT B to be the scalar
Returns: pointer to TENSOR C.
  C has the same form as A.
  For any COORDINATE M,
    C[M] is equal to A[M] * B

tensor *tensor_scl(tensor *C, tensor *A, tensor *B);

//Returns the partial with respect to A, and places it into C
tensor *tensor_scl_d_1(tensor *C, tensor *A, tensor *B);

//Returns the partial with respect to B, and places it into C
tensor *tensor_scl_d_2(tensor *C, tensor *A, tensor *B);

//Creates answer tensor to be used in function
tensor *tensor_scl_create(tensor *A, tensor *B);


Traditional fully connected layer
Inputs: pointers to TENSORs A and B, A is the activation layer and B is the parameter TENSOR
  FORM of A is ignored
  FORM[0] of B is to equal to A->length
Returns: pointer to TENSOR C
  FORM of C is equal to the FORM of B without the 0th index
  For any COORDINATE M,
    C[M] is equal to the sum of A[i]*B[{i,M}] as i increments

tensor *tensor_fll(tensor *C, tensor *A, tensor *B);

//Returns the partial with respect to A, and places it into C
tensor *tensor_fll_d_1(tensor *C, tensor *A, tensor *B);

//Returns the partial with respect to B, and places it into C
tensor *tensor_fll_d_2(tensor *C, tensor *A, tensor *B);

//Creates answer tensor to be used in function
tensor *tensor_fll_create(tensor *A, tensor *B);

*/
//#define FUNCTION_CT 4

//typedef uint8_t FUNCTION;

//tensor *(*function_table(FUNCTION f, uint8_t code))(tensor *, tensor *, tensor *);

#endif
