CC = clang
CFLAGS =  -Wpedantic -Wextra -Wall -Werror -Wno-unused-parameter -Wno-unused-variable

.phony: clean valtest_tensor valtest_network

demo: obj/demo.o obj/network.o obj/network_r.o obj/network_pderivative.o obj/tensor.o obj/tensor_r.o obj/tensor_functions.o obj/lx.o obj/lx_r.o obj/io.o
	$(CC)              $^ -o bin/demo -lm -lcurses
obj/demo.o: src/demo/demo.c
	$(CC) $(CFLAGS) -c $< -o $@


test_network: obj/test_network.o  obj/network.o obj/network_r.o obj/network_pderivative.o obj/tensor.o obj/tensor_r.o obj/tensor_functions.o obj/io.o
	$(CC)              $^ -o bin/test_network -lm


obj/test_network.o: src/test/network/test_network.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/network.o: src/network/network.c src/network/network.h src/project.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/network_r.o: src/network/r.c src/network/network.h src/io.c src/project.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/network_pderivative.o: src/network/pderivative.c src/network/pderivative.h src/network/network.h src/project.h
	$(CC) $(CFLAGS) -c $< -o $@



trainer: obj/trainer.o obj/lx.o obj/lx_r.o obj/tensor.o obj/tensor_r.o obj/io.o
	$(CC)              $^ -o bin/trainer -lm

obj/trainer.o: src/trainer/trainer.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/lx.o: src/trainer/lx.c src/trainer/lx.h  src/project.h 
	$(CC) $(CFLAGS) -c $< -o $@

obj/lx_r.o: src/trainer/r.c src/trainer/lx.h src/io.h src/project.h
	$(CC) $(CFLAGS) -c $< -o $@



test_tensor:  obj/test_tensor.o obj/tensor.o obj/tensor_r.o obj/tensor_functions.o obj/io.o
	$(CC)              $^ -o bin/test_tensor -lm


obj/test_tensor.o: src/test/tensor/test_tensor.c
	$(CC) $(CFLAGS) -c $< -o $@ 

obj/tensor.o: src/tensor/tensor.c src/tensor/tensor.h src/project.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/tensor_r.o: src/tensor/r.c src/tensor/tensor.h src/io.c src/project.h
	$(CC) $(CFLAGS) -c $< -o $@

obj/tensor_functions.o: src/tensor/functions.c src/tensor/functions.h src/tensor/tensor.h src/project.h
	$(CC) $(CFLAGS) -c $< -o $@


test_io: obj/test_io.o obj/io.o
	$(CC)              $^ -o bin/test_io 


obj/test_io.o: src/test/io/test_io.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/io.o: src/io.c src/io.h src/project.h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f *_TEST_SAVE*
	rm -f obj/*
	rm -f bin/*

valtest_io:
	make clean
	make test_io
	valgrind --leak-check=yes bin/test_io

valtest_tensor:
	make clean
	make test_tensor
	valgrind --leak-check=yes bin/test_tensor
	diff TENSOR_TEST_SAVE TENSOR_TEST_SAVE2

valtest_network:
	make clean
	make test_network
	valgrind --leak-check=yes bin/test_network
	diff NETWORK_TEST_SAVE NETWORK_TEST_SAVE2 
	
valtest_trainer:
	make clean
	make trainer	
	valgrind --leak-check=yes bin/trainer
	diff LX_TEST_SAVE LX_TEST_SAVE2

valtest_demo:
	make clean
	make demo
	valgrind --leak-check=yes bin/demo
