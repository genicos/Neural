CC = clang
CFLAGS =  -Wpedantic -Wextra -Wall -Werror -Wno-unused-parameter -Wno-unused-variable 

.phony: clean

test: test.o tensor.o tensor_r.o
		$(CC) test.o tensor.o tensor_r.o -o test

test.o: c_code/test.c c_code/project.h
	$(CC) $(CFLAGS) -c c_code/test.c

tensor.o: c_code/tensor/.c c_code/tensor/.h c_code/project.h
	$(CC) $(CFLAGS) -c c_code/tensor/.c -o tensor.o

tensor_r.o: c_code/tensor/.r c_code/tensor/.h c_code/project.h
	cp c_code/tensor/.r c_code/tensor/r.c
	$(CC) $(CFLAGS) -c c_code/tensor/r.c -o tensor_r.o
clean:
	rm test.o test tensor.o c_code/tensor/r.c

testval:
	make test
	valgrind --leak-check=yes ./test
