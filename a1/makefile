main: main.c matrix.c
	gcc -g -pthread main.c matrix.c

dep: ./get-dep
	./get-dep

clean*: clean clean-dep

clean:
	rm -f -r a.*

clean-dep: matrix.c matrix.h
	rm -f matrix.c matrix.h
