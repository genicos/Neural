/* NETWORK

*/

#include <inttypes.h>
#include "../tensor/.h"

typedef struct node{
  tensor *t;
  uint8_t causes_length;
  tensor **causes;
}
