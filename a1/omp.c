/*
    Author: Matt
*/
#include "matrix.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int n = 100;

void multiply(int** A, int** B, int** C) {
  int i, j, k;
  #pragma omp parallel shared(A, B, C) private(i, j, k)
  for (i = 0; i < n; i++) {
    #pragma omp for
    for (j = 0; j < n; j++) {
      for (k = 0; k < n; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

int main(int argc, char* argv[]) {

  int** matrix1 = mallocm(n, n);
  int** matrix2 = mallocm(n, n);
  int** product = callocm(n, n);

  srand(time(NULL));
  randm(matrix1, n, n, 20);
  randm(matrix2, n, n, 20);

  multiply(matrix1, matrix2, product);
  // printm(matrix1, n, n);
  // printf("\n");
  // printm(matrix2, n, n);
  // printf("\n");

  printf("OpenMP:\n");
  printm(product, n, n);
  printf("\n");

  freem(matrix1, n);
  freem(matrix2, n);
  freem(product, n);
  return 0;
}
