#ifndef NEURAL_C_CODE_TENSOR_H
#define NEURAL_C_CODE_TENSOR_H

#include "../project.h"
#include "../io.h"

typedef float       ELEMENT;              //The type for the TENSOR ELEMENTS
// ELEMENT must be float or double
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




void         save_ELEMENT     (IO *io, ELEMENT datum);
ELEMENT      read_ELEMENT     (IO *io);

void         save_FORM_LENGTH (IO *io, FORM_LENGTH datum);
FORM_LENGTH  read_FORM_LENGTH (IO *io);

void         save_FORM_ELEMENT(IO *io, FORM_ELEMENT datum);
FORM_ELEMENT read_FORM_ELEMENT(IO *io);

void         save_DATA_LENGTH (IO *io, DATA_LENGTH datum);
DATA_LENGTH  read_DATA_LENGTH (IO *io);


//tensor byte representation
//
//  typecode is defined in project.h
//  so() means sizeof()
// 
//  bytes                           meaning        representation
//  -------------------------------------------------------------
//  1                               ELEMENT        typecode       \
//  1                               FORM_LENGTH    typecode       |-preamble
//  1                               FORM_ELEMENT   typecode       |
//  1                               DATA_LENGTH    typecode       /
//  so(FORM_LENGTH)                 form_length    FORM_LENGTH
//  form_length * so(FORM_ELEMENT)  form           contiguous array of FORM_ELEMENT
//  data_length * so(ELEMENT)       data           contiguous array of ELEMENT
//
bool    tensor_save(char *file_name, tensor *t);  //Creates a file, appends tensor to it, closes file
bool    tensor_append(IO *io, tensor *t);         //Append tensor to file
tensor *tensor_extrct(IO *io);                    //Extract next tensor from file
tensor *tensor_read(char *file_name);             //Opens file, extracts tensor, closes file



//Creates a tensor without data
tensor* tensor_create(FORM_LENGTH form_length, FORM_ELEMENT *form);

//Allocates memory for tensor data
//memory is initialized to zero
ELEMENT* tensor_create_data(tensor *t);

void tensor_delete(tensor *t);



//Returns a tensor with the same form, and the same elements
tensor *tensor_copy(tensor *t);

void tensor_print(tensor *t, const char *printf_element_tag);

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
