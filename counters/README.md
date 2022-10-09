# CS50 Lab 3
## CS50 Fall 2022

### counters

A  `counter set` is a `set` of counters, each distinguished by an integer key. It's a `set` - each key can only occur once in the `set` - but instead of storing (key,item) pairs, it tracks a counter for each key.  It starts empty. Each time `counters_add` is called on a given key, that key's counter is incremented. The current counter value can be retrieved by asking for the relevant key.

### Usage

The *counters* module, defined in `counters.h` and implemented in `counters.c`, implements a counters of `in`, and exports the following functions:

```c
counters_t* counters_new(void);
int counters_add(counters_t* ctrs, const int key);
int counters_get(counters_t* ctrs, const int key);
bool counters_set(counters_t* ctrs, const int key, const int count);
void counters_print(counters_t* ctrs, FILE* fp);
void counters_iterate(counters_t* ctrs, void* arg, 
                      void (*itemfunc)(void* arg, 
                                       const int key, const int count));
void counters_delete(counters_t* ctrs);
```

### Assumptions

None, will return an error if input is not an int.

### Files

* `Makefile` - compilation procedure
* `counters.h` - the interface
* `counters.c` - the implementation
* `countersTest.c` - unit test driver
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make`.

### Testing

Tests for errors and edge cases.