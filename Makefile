CC = clang
CFLAGS =  -Wpedantic -Wextra -Wall -Werror -Wno-unused-parameter -Wno-unused-variable 

.phony: clean

test_tensor: test_tensor.o tensor.o tensor_r.o
		$(CC) test_tensor.o tensor.o tensor_r.o -o test_tensor

test_tensor.o: c_code/test_tensor.c c_code/project.h
	$(CC) $(CFLAGS) -c c_code/test_tensor.c

tensor.o: c_code/tensor/.c c_code/tensor/.h c_code/project.h
	$(CC) $(CFLAGS) -c c_code/tensor/.c -o tensor.o

tensor_r.o: c_code/tensor/.r c_code/tensor/.h c_code/project.h
	cp c_code/tensor/.r c_code/tensor/r.c
	$(CC) $(CFLAGS) -c c_code/tensor/r.c -o tensor_r.o
clean:
	rm -f test_tensor.o test_tensor tensor.o tensor_r.o c_code/tensor/r.c D_file

test_tensorval:
	make clean
	make test_tensor
	valgrind --leak-check=yes ./test_tensor
