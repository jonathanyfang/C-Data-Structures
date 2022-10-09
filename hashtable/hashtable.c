/* 
 * hashtable.h - header file for CS50 hashtable module
 *
 * A *hashtable* is a set of (key,item) pairs.  It acts just like a set, 
 * but is far more efficient for large collections.
 *
 * Jonathan Fang
 * October 9, 2022
 * CS50, Fall 2022
 */

#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash.h"
#include "../set/set.h"
#include <string.h>
#include "hashtable.h"
#include "../lib/mem.h"

/**************** global types ****************/
typedef struct hashtable {
    set_t **slots; 
    int num_slots;
} hashtable_t;

/**************** functions ****************/

/**************** hashtable_new ****************/
hashtable_t* hashtable_new(const int num_slots) {
    // Hashtable must have >0 slots
    if (num_slots > 0) {
        hashtable_t *ht = mem_malloc(sizeof(hashtable_t));
        ht->slots = mem_calloc(num_slots, sizeof(set_t*));
        ht->num_slots = num_slots;
        // Initialize empty sets
        for (int i = 0; i < num_slots; i++) {
            ht->slots[i] = set_new();
        }
        // Make sure memory was properly allocated
        if (ht == NULL || ht->slots == NULL) {
            return NULL;
        }
        return ht;
    } 
    else {
        return NULL; 
    }
}

/**************** hashtable_insert ****************/
bool hashtable_insert(hashtable_t* ht, const char* key, void* item) {
    if (ht != NULL && key != NULL && item != NULL) {
        // copy key
        // char *keycopy = mem_malloc(strlen(key) + 1);
        // strcpy(keycopy, key);
        // create a hash with keycopy
        int hash = (int) hash_jenkins(key, ht->num_slots);
        // mem_free(keycopy);
        if (ht->slots[hash] == NULL) {
            ht->slots[hash] = set_new();
            if(ht->slots[hash] == NULL) {
                return false;
            }
            ht->num_slots += 1;
        }
        return set_insert(ht->slots[hash], key, item);
    }
    return false;
}

/**************** hashtable_find ****************/
void* hashtable_find(hashtable_t* ht, const char* key) {
    if (ht != NULL && key != NULL) {
        // Hash key
        int hash = hash_jenkins(key, ht->num_slots);
        return set_find(ht->slots[hash], key);
    } 
    else {
        return NULL;
    }
}

/**************** hashtable_print ****************/
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item)) {
    if (fp != NULL) {
        if (ht != NULL) {
            for (int i = 0; i < ht->num_slots; i++) {
                // Print each set
                fprintf(fp, "Slot %d:", i);
                set_print(ht->slots[i], fp, (*itemprint));

            }
        } 
        else {
            fputs("(NULL)\n", fp);
        }
    }
}

/**************** hashtable_iterate ****************/
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) ) {
    if (ht != NULL && itemfunc != NULL) {
        // Iterate over slots and iterate through sets
        for (int i = 0; i < ht->num_slots; i++) {
            set_iterate(ht->slots[i], arg, (*itemfunc));
        }
    }
}

/**************** hashtable_delete ****************/
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) ) {
    if (ht != NULL) {
        // Iterate over slots
        for (int i = 0; i < ht->num_slots; i++) {
            // Free the sets
            set_delete(ht->slots[i], (*itemdelete));
        }
        // Free memory sets were kept in
        mem_free(ht->slots);
        mem_free(ht);
    }
#ifdef MEMTEST
    mem_report(stdout, "After hashtable_delete");
#endif
}

#endif // __HASHTABLE_H
