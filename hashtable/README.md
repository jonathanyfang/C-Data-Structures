# CS50 Lab 3
## CS50 Fall 2022

### hashtable

A `hashtable` is a `set` of _(key,item)_ pairs.  It acts just like a `set`, but is far more efficient for large collections.

### Usage

The *hashtable* module, defined in `hashtable.h` and implemented in `hashtable.c`, implements a set of `set*`, and exports the following functions:

```c
hashtable_t* hashtable_new(const int num_slots);
bool hashtable_insert(hashtable_t* ht, const char* key, void* item);
void* hashtable_find(hashtable_t* ht, const char* key);
void hashtable_print(hashtable_t* ht, FILE* fp, 
                     void (*itemprint)(FILE* fp, const char* key, void* item));
void hashtable_iterate(hashtable_t* ht, void* arg,
                       void (*itemfunc)(void* arg, const char* key, void* item) );
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) );
```
### Assumptions

file_readWords only reads alph, so anything inserted through stdin must be alphanumerical lowercase.

### Files

* `Makefile` - compilation procedure
* `hashtable.h` - the interface
* `hashtable.c` - the implementation
* `hash.h` - interface for jenkins hash
* `hash.h` - implemenation for jenkins hash
* `hashtableTest.c` - unit test driver
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make`.

### Testing

Tests for errors and edge cases. Also used myvalgrind to test for memory leakes. 
