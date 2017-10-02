#include "matrix.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct tdata {
  pthread_t tid;
  int id;
  int n;
  int threads;
  int result;
};

int **A, **B, **C;
/* 
  Author: Takeshi I.
  Note: This algorithm is O(n^3)
  Source: https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm
*/
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

/* 
  Author: Takeshi I.
*/
void* multiplym_pthread(void* param) {
  struct tdata* td = param;
  int threads = td->threads;
  int n = td->n;

  int steps = n / threads;
  if (threads > n) steps = n % threads;

  // For i from td->id to n:
  for (int i = td->id * steps; i < (td->id + 1) * steps; i++) {
    // For j from 1 to p:
    for (int j = 0; j < n; j++) {
      int sum = 0;
      // For k from 1 to m:
      for (int k = 0; k < n; k++) {
        sum += A[i][k] * B[k][j];
      }
      C[i][j] = sum;
    }
  }
  pthread_exit(NULL);
}

void randomfunc1() {
  // DELETE ME!
}

void randomfunc2() {
  // DELETE ME!
}

void randomfunc3() {
  // DELETE ME!
}

int main() {
  int n = 10, h = 2;
  int threads = 2;

  struct tdata td[threads];
  void* status;

  // Allocate memory
  A = mallocm(n, n);
  B = mallocm(n, n);
  C = mallocm(n, n);
  int** D = mallocm(n, n);

  // Generate random numbers
  srand(h);
  randm(A, n, n, h);
  randm(B, n, n, h);

  // Create threads
  for (int i = 0; i < threads; i++) {
    td[i] = (struct tdata){ .id = i, .n = n, .threads = threads };
    pthread_create(&td[i].tid, NULL, multiplym_pthread, &td[i]);
  }

  // Join threads
  for (int i = 0; i < threads; i++) {
    pthread_join(td[i].tid, &status);
  }

  // Print A, B, and C
  printf("A\n");
  printm(A, n, n);
  printf("\n");

  printf("B\n");
  printm(B, n, n);
  printf("\n");

  printf("C: Pthread\n");
  printm(C, n, n);
  printf("\n");

  printf("C: Sequential\n");
  multiplym(A, B, C, n);
  printm(C, n, n);

  // Free memory
  freem(A, n);
  freem(B, n);
  freem(C, n);
  return 0;
}