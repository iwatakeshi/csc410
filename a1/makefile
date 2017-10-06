default: seq pthread omp

seq: seq.c matrix.c
	gcc -g seq.c matrix.c -o seq.out

pthread: pthread.c matrix.c
	gcc -g -pthread pthread.c matrix.c -o pthread.out

omp: omp.c matrix.c
	gcc -g -fopenmp omp.c matrix.c -o omp.out

dep: ./get-dep
	./get-dep

clean*: clean clean-dep

clean:
	rm -f -r a.* seq.out pthread.out omp.out

clean-dep: matrix.c matrix.h
	rm -f matrix.c matrix.h
