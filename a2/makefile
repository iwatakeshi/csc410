default: dijkstra-c riemann

dijkstra-c: dijkstra.c
	gcc -g -fopenmp dijkstra.c -o dijkstra.out

riemann: riemann.c
	gcc -g -fopenmp riemann.c -o riemann.out -lm

test: ./test.sh
	./test.sh

clean:
	rm -f -r a.* dijkstra.out riemann.out