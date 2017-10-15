default: dijkstra-c riemann

dijkstra-c: dijkstra.c
	gcc -g -fopenmp dijkstra.c -o dijkstra.out

dijkstra-cpp: dijkstra.cpp
	g++ -g -std=c++14 dijkstra.cpp -o dijkstra.out

riemann: riemann.c
	gcc -g -fopenmp riemann.c -o riemann.out -lm

clean*: clean clean-dep

clean:
	rm -f -r a.* dijkstra.out riemann.out

clean-dep: matrix.c matrix.h
	rm -f matrix.c matrix.h
