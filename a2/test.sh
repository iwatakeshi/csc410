#!/bin/bash
TIMEFORMAT="%3R  %3U  %3S"
#sequential
echo "Dijkstra's Algorithm"
echo "Sequential"
echo "Nodes: Time(Real | User | Sys):"
for file in $(seq 1 3)
do
    #command line params -> ./dijkstras.out fileNumber(1->3): number of threads: enable threads 0 no 1 yes
    line=$(head -1 route$file.txt)
    timeOutput=$( { time ./dijkstra.out $file 1 0 > /dev/null; } 2>&1)
    echo "$line    $timeOutput"
done
#parallel
echo "Parallel"
echo "Nodes: Threads: Time(Real | User | Sys):"
for file in $(seq 1 3)
do
    #command line params -> ./dijkstras.out fileNumber(1->3): number of threads: enable threads 0 no 1 yes
    line=$(head -1 route$file.txt)
    timeOutput=$( { time ./dijkstra.out $file 5 1 > /dev/null; } 2>&1)
    echo "$line    5   ($timeOutput)"
done
for file in $(seq 1 3)
do
    #command line params -> ./dijkstras.out fileNumber(1->3): number of threads: enable threads 0 no 1 yes
    line=$(head -1 route$file.txt)
    timeOutput=$( { time ./dijkstra.out $file 8 1 > /dev/null; } 2>&1)
    echo "$line    8   ($timeOutput)"
done
#Riemann Sums testing-------------------------------------------------------------------------------
#sequential
echo "Riemann Sums LHS"
echo "Sequential"
echo "Starting X: Ending X: Rectangles: Time(Real | User | Sys):"
#starting x value
x_a = 0
#ending x value
x_b = 4
#number of rectangles
n = 5
for count in $(seq 0 5)
do
    #command line params -> ./riemann.out start x: end x: rectangles: number of threads: enable threads 0 no 1 yes
    timeOutput=$( { time ./riemann.out x_a x_b n 1 0 > /dev/null; } 2>&1)
    echo "     $timeOutput"
done
