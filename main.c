//
// Created by heros on 9/12/24.
//

#include <stdio.h>

#include "sieve_of_eratosthenes.h"
#include "trial_by_division.h"

#define TEST_NUMBER 100

int main(){
  list l;
  printf("testing trial by division %d:\n", TEST_NUMBER);
  l = trial_by_division(TEST_NUMBER);
  printf("found: %li\n", listSize(l));
  for(int i = 0; i < listSize(l); i++)
    printf("%u ", listGet(l, i));
  listFree(l);
  printf("\n\n");


  printf("testing sieve of eratosthenes %d:\n", TEST_NUMBER);
  l = sieve_of_eratosthenes(TEST_NUMBER);
  printf("found: %li\n", listSize(l));
  for(int i = 0; i < listSize(l); i++)
    printf("%u ", listGet(l, i));
  listFree(l);
  printf("\n\n");

  return 0;
}