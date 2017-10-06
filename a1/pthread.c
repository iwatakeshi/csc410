/* 
  Author: Takeshi I.
*/
#include "matrix.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tdata {
  pthread_t tid;
  int id;
  int n;
  int threads;
  int result;
};

int **A, **B, **C;

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

int main(int argc, char* argv[]) {
  int n = 100, h = 20;
  int threads = 2;

  struct tdata td[threads];
  void* status;

  // Allocate memory
  A = mallocm(n, n);
  B = mallocm(n, n);
  C = mallocm(n, n);

  // Generate random numbers
  srand(time(NULL));
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

  printf("Pthread: \n");
  printm(C, n, n);
  printf("\n");

  // Free memory
  freem(A, n);
  freem(B, n);
  freem(C, n);
  return 0;
}
