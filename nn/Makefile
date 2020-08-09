CFLAGS = -Wall -Werror -Wextra -Wpedantic
CC = clang -fno-color-diagnostics



test: test.o tensor.o foam.o
	$(CC) test.o tensor.o foam.o -o test

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

foam.o: foam.c foam.h
	$(CC) $(CFLAGS) -c foam.c


vectortest: vectortest.o vector.o
	$(CC) vectortest.o vector.o -o vectortest

vectortest.o: vectortest.c
	$(CC) $(CFLAGS) -c vectortest.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c


tensortest: tensortest.o tensor.o
	$(CC) tensortest.o tensor.o -o tensortest

tensortest.o: tensortest.c
	$(CC) $(CFLAGS) -c tensortest.c

tensor.o: tensor.c tensor.h
	$(CC) $(CFLAGS) -c tensor.c

.PHONY: clean
clean: 
	rm -f test test.o foam.o
	rm -f vectortest vectortest.o vector.o
	rm -f tensortest tensortest.o tensor.o

.PHONY: tensorval
tensorval:
	make tensortest
	valgrind --leak-check=yes ./tensortest
