#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

/* 
  Author: Takeshi I.
  Note: This algorithm is O(n^3)
  Source: https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm
*/
void multiplym(int** a, int** b, int n) {
  int** c = mallocm(n, n);
  // For i from 1 to n:
  for (int i = 0; i < n; i++) {
    // For j from 1 to p:
    for (int j = 0; j < n; j++) {
      int sum = 0;
      // For k from 1 to m:
      for (int k = 0; k < n; k++) {
        sum += a[i][k] * b[k][j];
      }
      c[i][j] = sum;
    }
  }
  copym(c, a, n, n);
  freem(c, n);
}

int main() {
  int n = 10, h = 2;
  int** a = mallocm(n, n);
  int** b = mallocm(n, n);
  srand(h);
  randm(a, n, n, h);
  randm(b, n, n, h);

  printm(a, n, n);
  printf("\n");
  printm(b, n, n);
  multiplym(a, b, n);
  printf("\n");
  printm(a, n, n);
  freem(a, n);
  freem(b, n);
  return 0;
}