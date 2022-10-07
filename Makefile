CC?=gcc
CFLAGS?=-g -Wall -Wextra

myapp: main.o vector.o permutation.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c myassert.h
	$(CC) $(CFLAGS) -c $^

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c $^

permutation.o: permutation.c permutation.h
	$(CC) $(CFLAGS) -c $^

# solution.o: solution.c solution.h
# 	$(CC) $(CFLAGS) -c $^

clean:
	rm myapp *.o *.gch