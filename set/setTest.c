#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "../lib/file.h"

static void itemprint(FILE* fp, const char* key, void* item);
static void itemcount(void* arg, const char* key, void* item);

/* **************************************** */
int main() {
  set_t* set1 = NULL;           // our set
  int keycount = 0;            // number of names put in the bag
  int setcount = 0;             // number of names found in a bag

  printf("Create first set...\n");
  set1 = set_new();
  if (set1 == NULL) {
    fprintf(stderr, "set_new failed for set1\n");
    return 1;
  }

  printf("\nTest with null set, good key, good item...\n");
  set_insert(NULL, "CS50", "A");
  printf("test with null key...\n");
  set_insert(set1, NULL, "A"); 
  printf("test with null item...\n");
  set_insert(set1, "CS50", NULL);
  printf("test with null set, null key...\n");
  set_insert(NULL, NULL, "A");
  printf("test with null set, null item...\n");
  set_insert(NULL, "CS50", NULL);
  printf("test with null item, null key...\n");
  set_insert(set1, NULL,  NULL);
  printf("test with null set, null key, null item...\n");
  set_insert(NULL, NULL, NULL);

  printf("\nCount (should be zero): ");
  setcount = 0;
  set_iterate(set1, &setcount, itemcount);
  printf("%d\n", setcount);

  printf("\nTesting set_insert...\n");
  set_insert(set1, "CS50", "ABC");
  set_insert(set1, "CS10", "DEF");
  
  printf("\nThe set:\n");
  set_print(set1, stdout, itemprint);
  printf("\n");

  printf("\ndelete the set...\n");
  set_delete(set1, NULL);

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
