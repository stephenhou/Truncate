#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "list.h"
#include <string.h>
#include <ctype.h>

int main(int argc, char** argv) {

	struct list* input = list_create();

	for(int i=1;i<argc;i++){
		list_append(input, argv[i]);
	}

  void print (element_t ev) {
    intptr_t e = (intptr_t) ev;
    printf ("%d\n", e);
  }

  void printS (element_t ev) {
    char* e = (char*) ev;
    printf ("%s\n", e);
  }

	void makeNumber(element_t* rv, element_t av) {
		char*  a = (char*)  av;
  	intptr_t* r = (intptr_t*) rv;
    if(*a == '0') {
      *r = 0;
    }

  	else if(strtol(a, 0, 0) == 0){
      intptr_t ret = -1;
  		*r = ret;
		}

 		else *r = (intptr_t) strtol(a, 0, 0);
	}

	void makeNull(element_t* rv, element_t av, element_t bv){
		char*  a = (char*)  av;
  	intptr_t  b = (intptr_t)  bv;
    char** r = (char**) rv;

    if(b > 0) {
      *a = 0;
      *r = a;
    }

    else{
		  *r = a;
    }
	}
  

	int isNotNeg(element_t av){
    intptr_t a = (intptr_t) av;
    return (a >= 0);
	}

	int isNotNull(element_t av){
    char* a = (char*) av;
    return !(*a == (intptr_t) NULL);
	}

  struct list* freeList = list_create();

	void truncate(element_t* rv, element_t av, element_t bv){
    intptr_t  a = (intptr_t)  av;
    char*  b = (char*)  bv;
    char** r = (char**) rv;

    if(a>strlen(b)){ 
      *r = b;
    }

    else {   
      char* temp = malloc(sizeof(char)*1000);
      strncpy(temp, b, a);
      *r = temp;
      list_append(freeList, (element_t) temp);
    }
	}

	void greater(element_t* rv, element_t av, element_t bv){
    intptr_t  a = (intptr_t)  av;
    intptr_t  b = (intptr_t)  bv;
    intptr_t* r = (intptr_t*) rv;

    if(b>a){
      *r = b;
    }
	}

	struct list* numbers = list_create();
	list_map1(makeNumber, numbers, input);

	struct list* stringNulls = list_create();
	list_map2(makeNull, stringNulls, input, numbers);

	struct list* filteredNums = list_create();
 	list_filter(isNotNeg, filteredNums, numbers);

 	struct list* filteredStrs = list_create();
 	list_filter(isNotNull, filteredStrs, stringNulls);

 	struct list* truncated = list_create();
 	list_map2(truncate, truncated, filteredNums, filteredStrs);
 	list_foreach (printS, truncated);
  list_foreach(free, freeList);

 	intptr_t max = 0;
 	list_foldl(greater, (element_t*) &max, filteredNums);
 	printf ("%ld\n", max);

  list_destroy (input);
  list_destroy (numbers);
  list_destroy (stringNulls);
  list_destroy (filteredNums);
  list_destroy (filteredStrs);
  list_destroy(truncated);
  list_destroy(freeList);
  
}
