
OBJS = countersTest.o counters.o ../lib/file.o ../lib/mem.o 
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

countersTest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

countersTest.o: counters.h ../lib/file.h
counters.o: counters.h
../lib/file.o: ../lib/file.h

.PHONY: test valgrind clean

# expects a file `test.names` to exist; it can contain any text.
test: countersTest
	./countersTest

# expects a file `test.names` to exist; it can contain any text.
valgrind: countersTest
	$(VALGRIND) ./countersTest

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f countersTest
	rm -f core
