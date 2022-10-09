
OBJS = hash.o hashtableTest.o hashtable.o ../lib/file.o ../lib/mem.o  ../set/set.o
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

MAKE = make
CC = gcc 
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

hashtableTest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ 

hashtableTest.o: hashtable.h ../lib/file.h
hashtable.o: hashtable.h ../set/set.h
hash.o: hash.h
../lib/file.o: ../lib/file.h 
  
.PHONY: test clean

valgrind: hashtableTest
	$(VALGRIND) ./hashtableTest

test: hashtableTest
	./hashtableTest

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f hashtableTest
	rm -f core
