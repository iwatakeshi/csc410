default: dijkstra

dijkstra: dijkstra.cpp matrix.c
	g++ -g -std=c++14 dijkstra.cpp -o a.out

riemann: riemann.c
	gcc -g -fopenmp riemann.c -o a.out

clean*: clean clean-dep

clean:
	rm -f -r a.*

clean-dep: matrix.c matrix.h
	rm -f matrix.c matrix.h
