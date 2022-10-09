#ifndef __SET_H
#define __SET_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"
#include "set.h"
#include <stdbool.h>

/* 
 * set.c - header file for CS50 set module
 *
 * A *set* maintains an unordered collection of (key,item) pairs;
 * any given key can only occur in the set once. It starts out empty 
 * and grows as the caller inserts new (key,item) pairs.  The caller 
 * can retrieve items by asking for their key, but cannot remove or 
 * update pairs.  Items are distinguished by their key.
 *
 * Jonathan Fang
 * October 9, 2022
 * CS50, Fall 2022
 */

/**************** local types ****************/
typedef struct setnode {
    char *key;
    void *item;
    struct setnode *next;
} setnode_t;

/**************** global types ****************/
typedef struct set {
    struct setnode *head;
} set_t;  // opaque to users of the module

/**************** local functions ****************/
static setnode_t *setnode_new(const char *key, void *item) {
    setnode_t *node = mem_malloc(sizeof(setnode_t));
    if (node == NULL) {
        return NULL; // Memory not properly allocated
    } 
    else { // initialize key and item
        node->key = mem_malloc(strlen(key) + 1);
        strcpy(node->key, key);
        node->item = item;
        return node;
    }
}

/**************** set_new ****************/
set_t *set_new(void) {
    set_t *set = mem_malloc(sizeof(set_t));
    if (set == NULL) {
        return NULL; // error allocating memory for set
    } else {
        // initialize contents of set structure
        set->head = NULL; 
        return set;
    }
}

/**************** set_find ****************/
void* set_find(set_t* set, const char* key) {
    if (set != NULL && key != NULL) {
        // iterate through set, return NULL if key not found
        for(setnode_t *node = set->head; node != NULL; node = node->next) {
            if (strcmp(key, node->key) == 0) {
                return node->item;
            }
        }
    }
    return NULL;
}

/**************** set_insert ****************/
bool set_insert(set_t* set, const char* key, void *item) {
    if (set != NULL && key != NULL && item != NULL) {
        // copy key
         // New key/value node
        // Make sure key doesn't already exist
        if (set_find(set, key) == NULL) {
            // Add new items to the head
            setnode_t* node = setnode_new(key, item);
            node->next = set->head;
            set->head = node;
            return true;
        }
    }
    return false;
}

/**************** set_print ****************/
void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item) ) {
     if (fp != NULL) {
        if (set != NULL) {
            fputc('{', fp);
            // Iterate over set
            for (setnode_t *node = set->head; node != NULL; node = node->next) {
                // Print current node (key, item)
                if (itemprint != NULL) {
                    (*itemprint)(fp, node->key, node->item);
                    // doesn't add comma at end of list
                    if (node->next != NULL) {
                        fputc(',', fp);
                    }
                }
            }
            fputc('}', fp);
            fputs("\n", fp);
        } else {
            fputs("(NULL)\n", fp);
        }
    }
}

/**************** set_iterate ****************/
void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) ) {
    if (set != NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
        for (setnode_t* node = set->head; node != NULL; node = node->next) {
            (*itemfunc)(arg, node->key, node->item); 
        }
    }
}

/**************** set_delete ****************/
void set_delete(set_t* set, void (*itemdelete)(void* item) ) {
    if (set != NULL) {
        setnode_t* node = set->head;
        while(node != NULL) {
            if (itemdelete != NULL) {         // if possible...
                (*itemdelete)(node->item);      // delete node's item
                (*itemdelete) (node->key);
            }
            setnode_t* next = node->next;     // remember what comes next
            mem_free(node->key);
            mem_free(node);                   // free the node
            node = next;                      // and move on to next
        }
        mem_free(set);
    }
#ifdef MEMTEST
  mem_report(stdout, "End of set_delete");
#endif
}

#endif // __SET_H
