

CC=gcc
CFLAGS=-g -Wall -Wextra

main.o: main.c myassert.h
	$(CC) $(CFLAGS) -c $^

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c $^

permutation.o: permutation.c permutation.h
	$(CC) $(CFLAGS) -c $^


solution.o: solution.c solution.h
	$(CC) $(CFLAGS) -c $^

myapp: main.o vector.o permutation.o solution.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm myapp *.o *.gch