#ifndef IO_H
#define IO_H

#include "project.h"
#include <stdlib.h>

#define BLOCK_SIZE   4096  //will load in chunks of size BLOCK_SIZE bytes
#define LARGEST_ATOM 8     //size of largest atomic type

//BLOCK_SIZE must be larger than LARGEST_ATOM

typedef struct IO{
  uint8_t buffer[BLOCK_SIZE+LARGEST_ATOM];
  uint8_t *needle; //next byte to be read
  uint8_t *end;    //1 byte after fread block
  FILE    *F;
} IO;

IO *io_create(FILE *F);

//not responsible for F
void io_delete(IO *io);

uint8_t  read_1_byte(IO *io);

uint16_t read_2_byte(IO *io);

uint32_t read_4_byte(IO *io);

uint64_t read_8_byte(IO *io);

//re-fill buffer
bool io_fill(IO *io);


void save_1_byte(IO *io, uint8_t datum);

void save_2_byte(IO *io, uint16_t datum);

void save_4_byte(IO *io, uint32_t datum);

void save_8_byte(IO *io, uint64_t datum);

bool io_empty(IO *io); //write a BLOCK

bool io_flush(IO *io); //write whatever is left


#endif
