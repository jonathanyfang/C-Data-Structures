
OBJS = setTest.o set.o ../lib/file.o ../lib/mem.o 
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

MAKE = make
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

setTest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

setTest.o: set.h ../lib/file.h
set.o: set.h
../lib/file.o: ../lib/file.h

.PHONY: test valgrind clean

# expects a file `test.names` to exist; it can contain any text.
test: setTest
	./setTest

# expects a file `test.names` to exist; it can contain any text.
valgrind: setTest
	$(VALGRIND) ./setTest

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f setTest
	rm -f core
