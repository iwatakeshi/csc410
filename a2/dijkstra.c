#include "matrix.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define NODES 6 //for static assignment
#define Inf 9999 //used as infinty

//function proto
void dijkstras_funct(int graph_matrix[NODES][NODES], int src_node);

//global solution graph for threads
int** sol_matrix;

int main() {
  //for static graph
  int graph_matrix[NODES][NODES] = {
    { 0, 7, 12, Inf, 7, Inf },
    { Inf, 0, 3, Inf, 12, Inf },
    { Inf, Inf, 0, Inf, Inf, Inf },
    { Inf, 10, Inf, 0, 25, Inf },
    { Inf, Inf, Inf, 12, 0, Inf },
    { Inf, Inf, Inf, Inf, Inf, 0 }
  };

  //Build solution matrix and fill with infinity
  sol_matrix = callocm(NODES, NODES, sizeof(int));

  //parallel here might be best?
  #pragma omp parallel for
  for (int _src_node = 0; _src_node < NODES; _src_node++) {
    printf("thread id: %d, threads: %d\n", omp_get_thread_num(), omp_get_num_threads());
    dijkstras_funct(graph_matrix, _src_node);
  }

  //print solution matrix
  for (int i = 0; i < NODES; i++) {
    for (int j = 0; j < NODES; j++) {
      if (sol_matrix[i][j] == Inf)
        printf("INF ");
      else
        printf("%3d ", sol_matrix[i][j]);
    }
    printf("\n");
  }

  // getchar();

  freem(sol_matrix, NODES);
  return 0;
}

//Dijkstras Function
void dijkstras_funct(int graph_matrix[NODES][NODES], int src_node) {
  int distance[NODES], pred[NODES];
  int visited[NODES], count, mindistance, i, j;
  int nextnode = 0;

  //initialize pred[], distance[] and visited[]
  for (i = 0; i < NODES; i++) {
    distance[i] = graph_matrix[src_node][i];
    pred[i] = src_node;
    visited[i] = 0;
    sleep(1);
  }

  distance[src_node] = 0; //always 0 to itself
  visited[src_node] = 1; //already visited yourself
  count = 1;

  while (count < NODES - 1) {
    mindistance = Inf;

    //nextnode gives the node at minimum distance
    for (i = 0; i < NODES; i++) {
      if (distance[i] < mindistance && !visited[i]) {
        mindistance = distance[i];
        nextnode = i;
      }
    }

    //check if a better path exists through nextnode
    visited[nextnode] = 1;
    for (i = 0; i < NODES; i++) {
      if (!visited[i])
        if (mindistance + graph_matrix[nextnode][i] < distance[i]) {
          distance[i] = mindistance + graph_matrix[nextnode][i];
          pred[i] = nextnode;
          sleep(1);
        }
    }
    //assign row data to solution matrix distance array holds all data
    //probably crit this, although each thread only gets one row
    for (i = 0; i < NODES; i++) {
      sol_matrix[src_node][i] = distance[i];
    }
    count++;

  } //end while
}