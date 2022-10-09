/* 
 * counters.c - header file for CS50 counters module
 *
 * A "counter set" is a set of counters, each distinguished by an integer key.
 * It's a set - each key can only occur once in the set - but instead of
 * storing (key,item) pairs, it tracks a counter for each key.  It starts
 * empty. Each time `counters_add` is called on a given key, that key's
 * counter is incremented. The current counter value can be retrieved by
 * asking for the relevant key.
 * 
 * Jonathan Fang
 * October 7, 2022
 * CS50, Fall 2022
 */

#ifndef __COUNTERS_H
#define __COUNTERS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "mem.h"
#include "counters.h"

/**************** local types ****************/
typedef struct counter { 
    int key;
    int count;
    struct counter *next;
} counter_t;

/**************** global types ****************/
typedef struct counters {
    struct counter *head;
} counters_t;

/**************** local functions ****************/
static counter_t *counter_new(int key) {
    // allocate memory for malloc
    counter_t *counter = mem_malloc(sizeof(counter_t));
    if (counter == NULL) {
        return NULL; // error allocating memory
    } 
    else {
        counter->key = key;
        counter->count = 0;
        return counter;
    }
}

/**************** counters_new ****************/
/* Create a new (empty) counter structure; return NULL if error. */
counters_t* counters_new(void) {
    counters_t *counters = mem_malloc(sizeof(counters_t));
    if (counters == NULL) {
        return NULL; // error allocating memory for counters
    } 
    else {
        // Initialize contents of counters structure
        counters->head = NULL;
        return counters;
    }
}

/**************** counters_add ****************/
/* Increment the counter indicated by key; key must be >= 0.
 * If the key does not yet exist, create a counter for it and initialize to 1.
 * Ignore if ctrs is NULL or key is negative.
 * Return the new value of the counter related to the inserted key
 */
int counters_add(counters_t* ctrs, const int key) {
    // Make sure valid pointer to counterset and key >= 0
    if (ctrs != NULL && key >= 0) {
        // If key exists, increment count
        counter_t* counter = ctrs->head;
        while(counter != NULL) {
            if (counter->key == key) {
                counter->count += 1;
                return counter->count;
            }
            counter = counter->next;
        }
        // If function doesn't return, key does not exist, initialize counter to 1
        counter_t* new_counter = counter_new(key);
        new_counter->count = 1;
        // Add new counter to the head
        if (new_counter != NULL) {
            new_counter->next = ctrs->head;
            ctrs->head = new_counter;
            return new_counter->count;
        }
    }
    // return 0 on error
    return 0;
}

/**************** counters_get ****************/
/* Return current value of counter associated with the given key;
 * return 0 if ctrs is NULL or if key is not found.
 */
int counters_get(counters_t* ctrs, const int key) {
    if (ctrs != NULL && key >= 0) {
        // Iterate to find the right key
        counter_t *counter = ctrs->head;
        while(counter != NULL) {
            if (counter->key == key) {
                return counter->count;
                }
            counter = counter->next;
        }
    }
    return 0; 
}

/**************** counters_set ****************/
/* Set the current value of counter associated with the given key;
 * If the key does not yet exist, create a counter for it and initialize to
 * the given value. Return false if ctrs is NULL, if key < 0, or count < 0, or if out of memory, otherwise return true.
 */
bool counters_set(counters_t* ctrs, const int key, const int count) {
    // valid pointer, key >= 0, count value >= 0
    if (ctrs != NULL && key >= 0 && count >= 0) {
        // Iterate to find the right key
        for (counter_t *counter = ctrs->head; counter != NULL; counter = counter->next) {
            if (counter->key == key) {
                counter->count = count;
                return true;
            }
        }
        // If function doesn't return, key wasn't found and we need to make a new counter
        counter_t *counter = counter_new(key);
        // Add new counter to the head
        if (counter != NULL) {
            counter->next = ctrs->head;
            ctrs->head = counter;
        }
        counters_set(ctrs, key, count);
    }
    return false;
}

/**************** counters_print ****************/
/* Print all counters; provide the output file.
 * Ignore if NULL fp. Print (null) if NULL ctrs.
 */
void counters_print(counters_t* ctrs, FILE* fp) {
    if (fp != NULL) {
        if (ctrs != NULL) {
            fputc('{', fp);
            for (counter_t *counter = ctrs->head; counter != NULL; counter = counter->next) {
                // print this node
                fprintf(fp, "%d:%d", counter->key, counter->count);
                // doesn't add comma at end of list
                if (counter->next != NULL) {
                    fputc(',', fp);
                }
            }
            fputc('}', fp);
            fputs("\n", fp);
        } else {
            fputs("(NULL)\n", fp);
        }
    }
}

/**************** counters_iterate ****************/
/* Iterate over all counters in the set (in undefined order):
 * call itemfunc for each item, with (arg, key, count).
 * If ctrs==NULL or itemfunc==NULL, do nothing.
 */
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count)) {
    if (ctrs != NULL && itemfunc != NULL) {
        // Call itemfunc with arg on each item
        for (counter_t *counter = ctrs->head; counter != NULL; counter = counter->next) {
            (*itemfunc)(arg, counter->key, counter->count);
        }
    }
}

/**************** counters_delete ****************/
/* Delete the whole counters. ignore NULL ctrs. */
void counters_delete(counters_t* ctrs) {
    if (ctrs != NULL) {
        // iterate through all counter_t and free
        counter_t *counter = ctrs->head;
        while(counter != NULL) {
            counter_t *next = counter->next;
            mem_free(counter);
            counter = next; // Iterate
        }
        mem_free(ctrs);
    }
#ifdef MEMTEST
  mem_report(stdout, "End of set_delete");
#endif
}

#endif // __COUNTERS_H
