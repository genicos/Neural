CC = clang
CFLAGS =  -Wpedantic -Wextra -Wall -Werror -Wno-unused-parameter -Wno-unused-variable 

.phony: clean valtest_tensor valtest_network


test_network: obj/test_network.o  obj/network.o obj/network_r.o obj/network_pderivative.o obj/tensor.o obj/tensor_r.o obj/tensor_functions.o
	$(CC) $^ -o bin/test_network


obj/test_network.o: src/test/network/test_network.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/network.o: src/network/network.c src/network/network.h src/project.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/network_r.o: src/network/r.c src/network/network.h src/project.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/network_pderivative.o: src/network/pderivative.c src/network/pderivative.h src/network/network.h src/project.h
	$(CC) $(CFLAGS) -c $< -o $@



test_tensor:  obj/test_tensor.o obj/tensor.o obj/tensor_r.o obj/tensor_functions.o
	$(CC) $^ -o bin/test_tensor


obj/test_tensor.o: src/test/tensor/test_tensor.c
	$(CC) $(CFLAGS) -c $< -o $@ 

obj/tensor.o: src/tensor/tensor.c src/tensor/tensor.h src/project.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/tensor_r.o: src/tensor/r.c src/tensor/tensor.h src/project.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/tensor_functions.o: src/tensor/functions.c src/tensor/functions.h src/tensor/tensor.h src/project.h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f *_TEST_SAVE
	rm -f obj/*
	rm -f bin/*

valtest_tensor:
	make clean
	make test_tensor
	valgrind --leak-check=yes bin/test_tensor

valtest_network:
	make clean
	make test_network
	valgrind --leak-check=yes bin/test_network
