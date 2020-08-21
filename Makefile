CC = clang
CFLAGS =  -Wpedantic -Wextra 

.phony: clean

test: test.o tensor.o
	$(CC) test.o tensor.o -o test

test.o: c_code/test.c c_code/project.h
	$(CC) $(CFLAGS) -c c_code/test.c

tensor.o: c_code/tensor.c c_code/tensor.h
	$(CC) $(CFLAGS) -c c_code/tensor.c 
clean:
	rm test.o test tensor.o

