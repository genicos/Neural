#include ".h"
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>

/*
type table
bit/s  meaning
-----  -------
1      0 - int, 1 - floating point
2      signed
3-8    size
*/

#define typecode(t)  isint(t) + (signed(t) << 1)

bool tensor_write(tensor *t){
  uint8_t element_type; 
}

tensor *tensor_read(){
  
}
