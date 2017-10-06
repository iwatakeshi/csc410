/*
    Author: Matt
*/
#include "matrix.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int n = 100;

void multiply(int** A, int** B, int** C) {
  int i, j, k, tid;
#pragma omp parallel for private(tid)
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      C[i][j] = 0;
      for (k = 0; k < n; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

int main(int argc, char* argv[]) {
  int** matrix1 = mallocm(n, n);
  int** matrix2 = mallocm(n, n);
  int** product = mallocm(n, n);

  srand(time(NULL));
  randm(matrix1, n, n, 20);
  randm(matrix2, n, n, 20);

  printm(matrix1, n, n);
  printm(matrix2, n, n);
  multiply(matrix1, matrix2, product);

  printf("OpenMP:\n");
  printm(product, n, n);
  printf("\n");

  freem(matrix1, n);
  freem(matrix2, n);

  return 0;
}