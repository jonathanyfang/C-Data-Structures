/* 
 * countersTest.c
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
#include "counters.h"
#include "../lib/file.h"

static void itemcount(void* arg, const int key, const int count);

/* **************************************** */
int main() {
  counters_t* counters = NULL;           // our counter
  int count = 0;             // count for counters

  printf("Create first counterset...\n");
  counters = counters_new();
  if (counters == NULL) {
    fprintf(stderr, "counters_new failed for counters\n");
    return 1;
  }
  
  printf("\nTest with null counters, good key...\n");
  counters_add(NULL, 7);
  printf("\nTest with good counters, negative key...\n");
  counters_add(counters, -5);
  printf("\nTest with null counters, negative key...\n");
  counters_add(NULL, -5);

  printf("\nCount (should be zero): ");
  counters_iterate(counters, &count, itemcount);
  printf("%d\n", count);

  printf("\nTesting counters_add...\n");
  printf("\nTest with key that does not yet exist...\n");
  counters_add(counters, 0);
  counters_print(counters, stdout);
  printf("\nTest with key that exists...\n");
  counters_add(counters, 0);
  counters_print(counters, stdout);

  printf("\nTesting counters_get...\n");
  printf("\nTesting with key that exists...\n");
  count = counters_get(counters, 0);
  printf("%d", count);
  printf("\nTesting with key that doesn't exist...\n");
  counters_get(counters, 1);
  printf("%d", count);

  printf("\nTesting counters_set...\n");
  printf("\nTesting with key that exists...\n");
  counters_set(counters, 0, 10);
  count = counters_get(counters, 0);
  printf("%d", count);
  printf("\nTesting with key that doesn't exist...\n");
  counters_set(counters, 1, 20);
  count = counters_get(counters, 1);
  printf("%d", count);

  printf("\n Number of keys: ");
  count = 0;
  counters_iterate(counters, &count, itemcount);
  printf("%d\n", count);

  printf("\nThe set:\n");
  counters_print(counters, stdout);
  printf("\n");

  printf("\ndelete the set...\n");
  counters_delete(counters);

  return 0;
}


static void itemcount(void* arg, const int key, const int count) {
  int* nitems = arg;

  if (nitems != NULL && key >= 0 && count != 0) {
    (*nitems)++; 
  }
}