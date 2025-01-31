//
// Created by heros on 9/12/24.
//

#include <stdio.h>

#include "dijkstra_prime_finding.h"
#include "sieve_of_eratosthenes.h"
#include "trial_by_division.h"
#include <sys/time.h>
#include <math.h>

#define TEST_NUMBER 100

#define UMBRAL_CONFIANZA 500
#define K 1000
#define STARTING_LENGTH (1024)
#define MAX_LENGTH 8388608
#define T_MAXIMO 1000000

double microsegundos() {
  struct timeval t;
  if (gettimeofday(&t, NULL) < 0 )
    return 0.0;
  return (t.tv_usec + t.tv_sec * 1000000.0);
}

double tiempo_test(prime numero, list function(prime)) {
  // Declarar variables
  double t, start, end;
  int i;

  //medición de tiempos
  start = microsegundos();
  listFree(function(numero));
  end = microsegundos();
  t = end - start;

  // En caso de que sea menor al umbral de confianza, repetirlo K veces
  if (t < UMBRAL_CONFIANZA) {

    // Conseguir el tiempo de K iteraciones
    start = microsegundos();
    for (i = 0; i < K; i++) {
      listFree(function(numero));
    }
    end = microsegundos();
    t = end - start;

    // Dividir el tiempo entre K iteraciones e imprimir (*)
    t /= K;
    printf("(*)");
  }

  return t;
}

void escribir_tabla(void function(prime), double cota_sub(double), double  cota_est(double), double cota_sobre(double)) {
  int num_nodos, i, j;
  double t = 0, exp;
  double * tabla = malloc(ceil(MAX_LENGTH/STARTING_LENGTH) * sizeof(double));
  for (num_nodos = STARTING_LENGTH, i = 0; num_nodos <= MAX_LENGTH && t < T_MAXIMO; num_nodos *= 2, i++) {
    t = tiempo_test(num_nodos, function);
    tabla[i] = t;
    printf("\t\t    %3d\t\t%14.3lf\t\t%2.10lf\t\t%2.10lf\t\t%2.10lf\n",num_nodos, t, t / cota_sub(num_nodos), t / cota_est(num_nodos), t / cota_sobre(num_nodos));
  }
  num_nodos /= 2;
  i--;

  //calcular exponente estimado, los exponentes del principio tienen menos peso que los del final (i debe de ser al menos 1) (lo que se calcula es la pendiente de la gráfica logarítmica)
  if(i > 0) {
    exp = (1 / pow(2, i)) * (log(tabla[1])-log(tabla[0])) / log(2); //habitualmente habría que dividirlo entre (log(num_nodos * 2) - log(num_nodos), pero por propiedades de logaritmos se simplifica a log(2)
    for (j = 1; j < i; j++) {
      exp += (pow(2,j) / pow(2, i)) * (log(tabla[j+1])-log(tabla[j])) / log(2);
    }
    printf("\nExponente estimado: %.2lf", exp);
    printf("\nTendencia con exponente estimado: %2.10lf\n", t / pow(num_nodos, exp));
  }
}

double cota_1_2(double valor){
  return pow(valor, 1.2);
}

double cota_1_1(double valor){
  return pow(valor, 1.1);
}

double cota_1(double valor){
  return pow(valor, 1);
}

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


  printf("testing dijkstra prime finder %d:\n", TEST_NUMBER);
  l = dijkstra_prime_finding(TEST_NUMBER);
  printf("found: %li\n", listSize(l));
  for(int i = 0; i < listSize(l); i++)
    printf("%u ", listGet(l, i));
  listFree(l);
  printf("\n\n");


  printf("\t\t      n\t\t\t  t(n)\t\t  t(n)/n^1.0\t\t t(n)/n^1.1\t\t    t(n)/n^1.2\n");
  escribir_tabla(trial_by_division, cota_1, cota_1_1, cota_1_2);
  printf("\n\n");


  printf("\t\t      n\t\t\t  t(n)\t\t  t(n)/n^1.0\t\t t(n)/n^1.1\t\t    t(n)/n^1.2\n");
  escribir_tabla(sieve_of_eratosthenes, cota_1, cota_1_1, cota_1_2);
  printf("\n\n");


  printf("\t\t      n\t\t\t  t(n)\t\t  t(n)/n^1.0\t\t t(n)/n^1.1\t\t    t(n)/n^1.2\n");
  escribir_tabla(dijkstra_prime_finding, cota_1, cota_1_1, cota_1_2);

  return 0;
}