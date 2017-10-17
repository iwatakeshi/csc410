# Getting Started

## Build
Run `make` to compile `dijkstra.c` and `riemann.c`.

## Run

## Dijkstra's Algorithm
Route files are provided in this directory. They are named `routes%d.txt` where `%d` is a digit from 1 to 3.  NOTE: must pass all arguments or program will use defualt values.  ./dijkstra.out [file number] [number of threads] [enable threads, 0 no, 1 yes]
### Sequential
To run the program, provide the file number to load, the number of threads, and 0 to disable threads as in the example below and the program would run sequentially.  
```bash
./dijkstra.out 1 1 0
```
### Parallel
To run the program in parallel, provide the file number to load and specifiy the number of threads and whether the program should run in parallel as in the example below.
```bash
./dijkstra.out 1 5 1
```
### Custom Data Files
The file format is as follows:
6       <-The number of nodes for the graph
0 1 3   <-Source node: Destination node: Wieght of edge
2 5 12
.....
NOTE: 0 based indexing, so we have 6 nodes, our sixth node is 5, so we can't do:
6
1 6 12  <-seg fualt, there is no sixth node
.....
Also files have to be named 'routes%d.txt' where '%d' is the file number

## Riemann's Sum Algorithm
NOTE: must pass all arguments or program will use defualt values.  ./riemann.out [starting x value] [ending x value] [number of rectangles] [number of threads] [enable threads, 0 no, 1 yes]

### Sequential
To run the program, provide the starting point, ending point, and the number of rectangles to use as in the xample below.
```bash
./riemann.out 0 20 3 1 0
```
### Parallel
To run the program in parallel, simply add a 1 at the end of the arguments list as in the example below.
```bash
./riemann.out 0 20 3 5 1
```

## Test
To run the test script that returns the time it took to complete based on the inputs run the following.
```bash
make test
```
Add Comment Collapse