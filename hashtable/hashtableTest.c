/* 
 * hashtableTest.c - test program for CS50 hashtable module
 *
 * usage: read names from stdin, each on one line
 *
 * Jonathan Fang
 * October 9, 2022
 * CS50, Fall 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "../lib/file.h"

static void itemprint(FILE* fp, const char* key, void* item);
static void itemcount(void* arg, const char* key, void* item);

/* **************************************** */
int main() {
  hashtable_t* hashtable1 = NULL;           // our first hashtable
  int count1 = 0;            // counter for iterating through hashtable1

  printf("Create first hashtable...\n");
  hashtable1 = hashtable_new(10);
  if (hashtable1 == NULL) {
    fprintf(stderr, "hashtable_new failed for hashtable1\n");
    return 1;
  }

  printf("\nTest with null hashtable, good key, good item...\n");
  hashtable_insert(NULL, "CS50", "A");
  printf("test with null key...\n");
  hashtable_insert(hashtable1, NULL, "A"); 
  printf("test with null item...\n");
  hashtable_insert(hashtable1, "CS50", NULL);
  printf("test with null hashtable, null key...\n");
  hashtable_insert(NULL, NULL, "A");
  printf("test with null hashtable, null item...\n");
  hashtable_insert(NULL, "CS50", NULL);
  printf("test with null item, null key...\n");
  hashtable_insert(hashtable1, NULL,  NULL);
  printf("test with null hashtable, null key, null item...\n");
  hashtable_insert(NULL, NULL, NULL);

  printf("\nCount (should be zero): ");
  count1 = 0;
  hashtable_iterate(hashtable1, &count1, itemcount);
  printf("%d\n", count1);

  printf("\nTesting hashtable_insert...\n");
  hashtable_insert(hashtable1, "CS50", "ABC");
  hashtable_insert(hashtable1, "CS10", "DEF");
  printf("\nInserting an existing key...\n");
  hashtable_insert(hashtable1, "CS50", "GHI");
  
  printf("\nThe hashtable:\n");
  hashtable_print(hashtable1, stdout, itemprint);
  printf("\n");

  printf("\ndelete hashtable1...\n");
  hashtable_delete(hashtable1, NULL);

  return 0;
}


static void itemcount(void* arg, const char* key, void* item) {
  int* nitems = arg;

  if (nitems != NULL && key != NULL && item != NULL) {
    (*nitems)++; 
  }
}

void itemprint(FILE* fp, const char* key, void* item) {
  const char* keystr = key;
  char* itemstr = item; 
  if (key == NULL || item == NULL) {
    fprintf(fp, "(null)");
  }
  else {
    fprintf(fp, "\"(%s,%s)\"", keystr,itemstr); 
  }
}
