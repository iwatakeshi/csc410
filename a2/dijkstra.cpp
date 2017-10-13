#include <algorithm>
#include <queue>
#include <stdio.h>
#include <tuple>
#include <vector>

const int Infinity = 9999;

/*
  Dijkstra's Algorithm Sequential
  Contributor: Takeshi
  Credit: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Using_a_priority_queue
*/
void dijkstra(std::vector<std::vector<int>> G, long unsigned size, int source) {

  // Define a type for a pair
  typedef std::pair<int, int> P;
  // Createa vertex set Q
  std::priority_queue<P, std::vector<P>, std::greater<P>> Q;

  // Unknown distance from source to v
  std::vector<unsigned int> distance(size, Infinity);
  // Predecessor of v
  std::vector<int> previous(size, -1);

  // Initialization
  distance[source] = 0;

  //
  for (int v = 0; v < size; v++) {
    Q.push(std::make_pair(v, distance[v]));
  }
  
  // The main loop
  while (!Q.empty()) {
    // auto p = Q.top();
    auto u = Q.top().first;
    Q.pop();
    // printf("u: %d, v: %d\n", u, std::get<1>(p));
    for (int v = 0; v < size; v++) {
      // If an adjacent node exists
      if (G[u][v] > 0) {
        int alt = distance[u] + G[u][v];
        if (alt < distance[v]) {
          distance[v] = alt;
          previous[v] = u;
          Q.push(std::make_pair(v, distance[v]));
        }
      }
    }
  }

  char letters[26] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
    'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
  };
  for (int i = 0; i < size; i++) {
    if (distance[i] == Infinity || distance[i] == 0) {
      printf("Distance from %c to %c: -- \n", letters[source], letters[i]);
    } else {
      printf("Distance from %c to %c: %d\n", letters[source], letters[i], distance[i]);
    }
  }
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
  std::vector<std::vector<int>> G = {
    { 0, 11, 4, 20, 0, 0 },
    { 0, 0, 0, 6, 0, 0 },
    { 0, 2, 0, 15, 7, 0 },
    { 0, 0, 0, 0, 0, 5 },
    { 0, 0, 0, 3, 0, 30 },
    { 0, 0, 0, 0, 18, 0 },
  };

  char letters[26] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
    'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
  };

  printf("Number of nodes: %lu\n", G.size());
  for (int i = 0; i < G.size(); i++) {
    printf("%6c", letters[i]);
  }
  printf("\n");
  for (int i = 0; i < G.size(); i++) {
    printf("%c", letters[i]);
    for (int j = 0; j < G.size(); j++) {
      printf("%6.2d", G[i][j]);
    }
    printf("\n");
  }

  for (int source = 0; source < G.size(); source++) {
    dijkstra(G, G.size(), source);
  }

  return 0;
}