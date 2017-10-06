/* 
  Author: Takeshi I.
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "matrix.h"

void multiplym(int** a, int** b, int** c, int n) {
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
}

int main() {
  int n = 100, h = 20;
  int threads = 2;
  int **A, **B, **C;

  // Allocate memory
  A = callocm(n, n);
  B = callocm(n, n);
  C = callocm(n, n);

  // Generate random numbers
  srand(time(NULL));
  randm(A, n, n, 20);
  randm(B, n, n, 20);
  
  multiplym(A, B, C, n);
  printf("Sequential: \n");
  printm(C, n, n);
	printf("\n");
  
  // Free memory
  freem(A, n);
  freem(B, n);
  freem(C, n);
  return 0;
}