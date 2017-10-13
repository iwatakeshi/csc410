#include <algorithm>
#include <queue>
#include <stdio.h>
#include <tuple>
#include <vector>

/* 
  Note: A different branch is used for matrix.h!
  See https://github.com/iwatakeshi/matrix.h/tree/change-mallocm-callocm-signatures
*/

const int Infinity = INT_MAX;

/*
  mindistance(Destination value, Marked Value + Edge Weight)
  The destination value is the destination vertex (i.e. Y) column.
  The marked value is the source vertex (i.e. X) column.
  The edge weight of the edges that connects the source and destination.
*/
// int mindistance(int a, int b) {
//   if (a < b) return a;
//   return b;
// }

void dijkstra(std::vector<std::vector<int>> G, int size, int source) {
  int distance[size];
  int previous[size];
  for (int i = 0; i < size; i++) {
    distance[i] = Infinity;
    previous[i] = 0;
  }
  distance[source] = 0;

  typedef std::pair<int, int> P;
  std::priority_queue<P, std::vector<P>, std::greater<P>> Q;

  Q.push(std::make_pair(source, G[source][source]));

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (G[i][j] > 0 && G[i][j] != G[source][source]) {
        Q.push(std::make_pair(i, G[i][j]));
      }
    }
  }

  while (!Q.empty()) {
    auto p = Q.top();
    Q.pop();
    auto u = std::get<1>(p);
    for (int v = 0; v < size; v++) {
      // If an adjacent node exists
      if (G[u][v] > 0) {
        int alt = distance[u] + G[u][v];
        if (alt < distance[v]) {
          distance[v] = alt;
          previous[v] = alt;
          Q.push(std::make_pair(u, distance[v]));
        }
      }
    }
  }

  for (int i = 1; i < size; i++) {
    if (distance[i] == Infinity || distance[i] == 0) {
      printf("Distance from %d to %d: \n", source, i);
    } else {
      printf("Distance from %d to %d: %d", source, i, distance[i]);
    }
  }
  // for (int i = 1; i < graphSize; i++) {
  //   printPath(previous, source, i);
  //   printf("\n");
  // }
}

/* 
  INPUT:
    * # of nodes
    * # of edges
    * source
    * destination
    * cost
*/

int main() {
  int n = 5;
  std::vector<std::vector<int>> G;
  G.resize(5);
  for (int i = 0; i < 5; i++) {
    G[i].push_back(i);
    std::random_shuffle(G.begin(), G.end());
    for (int j = 0; j < 5; j++) {
      G[i].push_back(j);
      std::random_shuffle(G[i].begin(), G[i].end());
    }
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      printf("%2d", G[i][j]);
    }
    printf("\n");
  }

  dijkstra(G, n, 2);

  return 0;
}