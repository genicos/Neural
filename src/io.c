#include "io.h"

void io_delete(IO *io){
  free(io);
}

IO *io_create(FILE *F){
  if(!F)
    return NULL;
  
  IO *io = (IO *)malloc(sizeof(IO));
  if(!io)
    return NULL;
  
  io->F = F;
  
  io->end = io->needle = io->buffer;
  
  return io;
}



bool io_fill(IO *io){
  if(!io)
    return false;
  
  if(io->end - io->needle > LARGEST_ATOM)   //if more to be read
    return true;
  
  
  for(uint8_t i = 0; i < io->end - io->needle; i++){ //moving unread bytes to beggining
    io->buffer[i] = io->needle[i];
  }
  
  
  io->needle = (io->end - io->needle) + io->buffer;  //placing needle after moved bytes

  io->end = io->needle + fread(io->needle, 1, BLOCK_SIZE, io->F); //Reading BLOCK
  
  io->needle = io->buffer;                           //re placing needle at beggining
  
  return io->end != io->needle;                      //false if no bytes left
}

bool io_empty(IO *io){
  if(!io)
    return false;
  
  if(io->needle - io->buffer < BLOCK_SIZE)  // ensuring that a BLOCK can be written
    return true;
  
  if(!fwrite(io->buffer, 1, BLOCK_SIZE, io->F)) //Writing BLOCK
    return false;
  
  for(uint8_t i = 0; i < io->needle - io->buffer - BLOCK_SIZE; i++){ 
    io->buffer[i] = io->buffer[BLOCK_SIZE + i];  //moving unwritten bytes to the beggining
  }
  
  io->needle -= BLOCK_SIZE; //placing needle after moved bytes
  
  return true;
}

bool io_flush(IO *io){
  if(!io)
    return false;
  
  return fwrite(io->buffer, 1, io->needle - io->buffer, io->F);
}





uint8_t read_1_byte(IO *io){
  uint8_t ans = 0;
  
  if(io_fill(io)){
    ans += io->needle[0];
  
    io->needle += 1;
  }
  
  return ans;
}

uint16_t read_2_byte(IO *io){
  uint16_t ans = 0;
  
  if(io_fill(io)){
    ans +=           io->needle[0];
    ans += (uint64_t)io->needle[1] << 8;
    
    io->needle += 2;
  }
  
  return ans;
}

uint32_t read_4_byte(IO *io){
  uint32_t ans = 0;
  
  if(io_fill(io)){
    ans +=           io->needle[0];
    ans += (uint64_t)io->needle[1] << 8;
    ans += (uint64_t)io->needle[2] << 16;
    ans += (uint64_t)io->needle[3] << 24;
    
    io->needle += 4;
  }
  
  return ans;
}

uint64_t read_8_byte(IO *io){
  uint64_t ans = 0;
  
  if(io_fill(io)){
    ans +=           io->needle[0];
    ans += (uint64_t)io->needle[1] << 8;
    ans += (uint64_t)io->needle[2] << 16;
    ans += (uint64_t)io->needle[3] << 24;
    ans += (uint64_t)io->needle[4] << 32;
    ans += (uint64_t)io->needle[5] << 40;
    ans += (uint64_t)io->needle[6] << 48;
    ans += (uint64_t)io->needle[7] << 56;
    
    io->needle += 8;
  }
  
  return ans;
}

void save_1_byte(IO *io, uint8_t datum){
  
  io->needle[0] = datum;
  
  io->needle += 1;
  
  io_empty(io);
}

void save_2_byte(IO *io, uint16_t datum){
  
  io->needle[0] = datum;
  io->needle[1] = datum >> 8;
  
  io->needle += 2;
  
  io_empty(io);
}

void save_4_byte(IO *io, uint32_t datum){
  
  io->needle[0] = datum;
  io->needle[1] = datum >> 8;
  io->needle[2] = datum >> 16;
  io->needle[3] = datum >> 24;
  
  io->needle += 4;
  
  io_empty(io);
}

void save_8_byte(IO *io, uint64_t datum){
  
  io->needle[0] = datum;
  io->needle[1] = datum >> 8; 
  io->needle[2] = datum >> 16;
  io->needle[3] = datum >> 24;
  io->needle[4] = datum >> 32;
  io->needle[5] = datum >> 40;
  io->needle[6] = datum >> 48;
  io->needle[7] = datum >> 56;

  io->needle += 8;
  
  io_empty(io);
}
