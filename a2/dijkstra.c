////////////////////////////////////////
//Group: Terrible Tees
//Authors:
//	Takeshi Iwana
//	Tye Tinsley
////////////////////////////////////////

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

<<<<<<< HEAD
=======
#define NODES 6 //for static assignment
>>>>>>> origin/master
#define Inf 9999 //used as infinty

//function proto
void dijkstras_funct(int _nodes, int src_node);
void make_graph(FILE *fp, int _nodes);
void print_sol(int _nodes);

//global solution graph for threads
int** sol_matrix;
//probably should just pass this matrix as a parameter into the function and
//reduce its scope to main but meh!
int** graph_matrix;

int main(int argc, char *argv[]) {

	int fileNum = 1;//this will be argv 1 but set here as defualt
	int threads = 5;//this will be argv 2 set as defualt
	if (argc == 3)
	{
		fileNum = atoi(argv[1]);
		threads = atoi(argv[2]);
	}

	omp_set_num_threads(threads);

<<<<<<< HEAD
	//File IO stuff for dynamic graphs from files
	int nodes;
	char fileSelect[12];
	sprintf(fileSelect, "routes_%d.txt", fileNum);
	FILE *inFile;
	inFile = fopen(fileSelect, "r");
	fscanf(inFile, "%d", &nodes);
	
	//build graph from file
	make_graph(inFile, nodes);
	fclose(inFile);
=======
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
>>>>>>> origin/master

  //Build solution matrix and fill with infinity
  sol_matrix = callocm(nodes, nodes, sizeof(int));

<<<<<<< HEAD
  //parallel here as every thread will get a row to calculate
  //#pragma omp parallel for
  for (int _src_node = 0; _src_node < nodes; _src_node++) {
    dijkstras_funct(nodes, _src_node);
  }

	//print solution matrix
	print_sol(nodes);

  freem(sol_matrix, nodes);
  freem(graph_matrix, nodes);
=======
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
>>>>>>> origin/master
  return 0;
}

//Dijkstras Function
void dijkstras_funct(int _nodes, int src_node) {
	int *distance, *pred, *visited;
	distance = malloc(_nodes * sizeof(int));
	pred = malloc(_nodes * sizeof(int));
	visited = malloc(_nodes * sizeof(int));
	int count, mindistance, i, j;
	int nextnode = 0;

  //initialize pred[], distance[] and visited[]
  for (i = 0; i < _nodes; i++) {
    distance[i] = graph_matrix[src_node][i];
    pred[i] = src_node;
    visited[i] = 0;
    sleep(1);
  }

  distance[src_node] = 0; //always 0 to itself
  visited[src_node] = 1; //already visited yourself
  count = 1;

<<<<<<< HEAD
  while (count < _nodes - 1) {
=======
  while (count < NODES - 1) {
>>>>>>> origin/master
    mindistance = Inf;

    //nextnode gives the node at minimum distance
    for (i = 0; i < _nodes; i++) {
      if (distance[i] < mindistance && !visited[i]) {
        mindistance = distance[i];
        nextnode = i;
      }
    }

    //check if a better path exists through nextnode
    visited[nextnode] = 1;
    for (i = 0; i < _nodes; i++) {
      if (!visited[i])
        if (mindistance + graph_matrix[nextnode][i] < distance[i]) {
          distance[i] = mindistance + graph_matrix[nextnode][i];
          pred[i] = nextnode;
          sleep(1);
        }
    }
    //assign row data to solution matrix distance array holds all data
    //probably crit this, although each thread only gets one row
    for (i = 0; i < _nodes; i++) {
      sol_matrix[src_node][i] = distance[i];
    }
    count++;

  } //end while
	//cleanup mallocs
	free(distance);
	free(pred);
	free(visited);
}


void make_graph(FILE *fp, int _nodes)
{
	int cntr = 0;//keep count of # from file
	int i, j, hldr;
	graph_matrix = callocm(_nodes, _nodes, sizeof(int));

	while (!feof(fp))
	{
		fscanf(fp, "%d", &hldr);
		if (cntr == 0)//first index
			i = hldr;
		else if (cntr == 1)//2nd index
			j = hldr;
		else if (cntr == 2)//weight of edge
		{
			graph_matrix[i][j] = hldr;
			cntr = 0;//reset for next triplet
			continue;//jump the increment
		}
		cntr++;
	}

	//re-pops the zeros to int_max/infinity
	for (int i = 0; i < _nodes; i++) 
	{
		for (int j = 0; j < _nodes; j++) 
		{
			if ((graph_matrix[i][j] == 0) && (i != j))//Callocm assigns all cells to zero
				graph_matrix[i][j] = Inf;
		}
	}
}


void print_sol(int _nodes)
{
	for (int i = 0; i < _nodes; i++) {
		for (int j = 0; j < _nodes; j++) {
			if (sol_matrix[i][j] == Inf)
				printf("INF ");
			else
				printf("%3d ", sol_matrix[i][j]);
		}
		printf("\n");
	}
}