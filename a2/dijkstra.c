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
	int threads = 1;//this will be argv 2 set as defualt
	int t_enable = 0;//enable threads 0 is no
	if (argc == 4)
	{
		fileNum = atoi(argv[1]);
		threads = atoi(argv[2]);
		t_enable = atoi(argv[3]);
	}

	

	//File IO stuff for dynamic graphs from files
	int nodes;
	char fileSelect[12];
	sprintf(fileSelect, "route%d.txt", fileNum);
	FILE *inFile;
	inFile = fopen(fileSelect, "r");
	fscanf(inFile, "%d", &nodes);
	
	//build graph from file
	make_graph(inFile, nodes);
	fclose(inFile);

  //Build solution matrix and fill with infinity
  sol_matrix = callocm(nodes, nodes, sizeof(int));

  //parallel here as every thread will get a row to calculate
  if(t_enable == 1)//use threads
  {
	printf("Dijkstra's Shortest Path Algorithm:\n");
	printf("With %d nodes, using input file: [routes%d.txt]\n",nodes,fileNum);
	printf("Parallel with %d threads:\n\n",threads);
	omp_set_num_threads(threads);//set number of threads
	#pragma omp parallel for
  	for (int _src_node = 0; _src_node < nodes; _src_node++) {
			// printf("thread id: %d, num of threads: %d\n", omp_get_thread_num(), omp_get_num_threads());
			dijkstras_funct(nodes, _src_node);
  	}
  }
  else//don't use threads
  {
	printf("Dijkstra's Shortest Path Algorithm:\n");
	printf("With %d nodes, using input file: [routes%d.txt]\n",nodes,fileNum);
	printf("Sequential:\n\n");
  	for (int _src_node = 0; _src_node < nodes; _src_node++) {
    		dijkstras_funct(nodes, _src_node);
  	}
  }

	//print solution matrix
	print_sol(nodes);

  freem(sol_matrix, nodes);
  freem(graph_matrix, nodes);
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
  }

  distance[src_node] = 0; //always 0 to itself
  visited[src_node] = 1; //already visited yourself
  count = 1;

  while (count < _nodes - 1) {
    sleep(1);
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