# Getting Started

## Build

Run `make` to compile `dijkstra.c` and `riemann.c`.

## Run

### Dijkstra's Algorithm

Route files are provided in this directory. They are named `routes%d.txt` where `%d` is a digit from 1 to 3.

To run the program, provide the file number to load as in the example below and the program would run sequentially.

```bash
./dijkstra.out 1 1 0
```

To run the program in parallel, provide the file number to load and specifiy the number of threads and whether the program should run in parallel as in the example below.

```bash
./dijkstra.out 1 5 1
```

### Riemann's Sum Algorithm

To run the program, provide the starting point, ending point, and the number of rectangles to use as in the xample below.

```bash
./riemann.out 0 20 3
```

To run the program in parallel, simply add a 1 at the end of the arguments list as in the example below.

```bash
./riemann.out 0 20 3 1
```
