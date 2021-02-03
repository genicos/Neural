#include "../project.h"
#include "../network/pderivative.h"
#include "../io.h"

typedef uint32_t EXAMPLES_COUNT;
typedef uint32_t INPUTS_COUNT;


typedef struct lx{
  EXAMPLES_COUNT examples_count;
  INPUTS_COUNT inputs_count;
  tensor **examples; //contiguos 2d array, of form {examples_count, inputs_count + 1}
    //major dimension is examples,
    //minor dimension is tensors of an example
  bool examples_responsibility;
} lx;


void lx_delete(lx *x);

lx *lx_create(uint32_t examples_count, uint32_t inputs_count, tensor **examples);


tensor *lx_example_input(lx *x, uint32_t example, uint32_t input);

tensor *lx_example_output(lx *x, uint32_t example);



void           save_EXAMPLES_COUNT(IO *io, EXAMPLES_COUNT datum);
EXAMPLES_COUNT read_EXAMPLES_COUNT(IO *io);

void           save_INPUTS_COUNT  (IO *io, INPUTS_COUNT datum);
INPUTS_COUNT   read_INPUTS_COUNT  (IO *io);



bool lx_save(char *file_name, lx *x);
bool lx_append(IO *io, lx *x);
lx  *lx_extrct(IO *io);
lx  *lx_read(char *file_name);
