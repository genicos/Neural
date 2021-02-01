#include "../../project.h"
#include "../../io.h"

#include <stdio.h>

int main(){
  
  FILE *F = fopen("src/test/io/TEXT", "r");
  if(!F){
    printf("File not found\n");
    return 1;
  } 
  IO *io = io_create(F);
  
  
  printf("%d, %d, %d, %d \n, %d, %d, %d \n, %d %d %d %d \n", 
  read_1_byte(io), read_2_byte(io), read_4_byte(io), read_1_byte(io),
  read_2_byte(io), read_4_byte(io), read_1_byte(io),
  read_2_byte(io), read_1_byte(io), read_4_byte(io), read_1_byte(io));
  
  FILE *N = fopen("OUT", "w");
  IO *nio = io_create(N);
  
  save_1_byte(nio, 65);
  save_2_byte(nio, 16962);
  save_4_byte(nio, 1128481603);
  save_1_byte(nio, 10);
  
  io_flush(nio);
  
  fclose(F);
  fclose(N);
  io_delete(nio);
  io_delete(io);
  return 0;
}
