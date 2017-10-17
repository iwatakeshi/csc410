#!/bin/bash
TIMEFORMAT="%3R  %3U  %3S"
#sequential
echo ""
echo "STARTING DIJKSTRAS ALGORITHM (SHORTEST PATH)"
echo ""
echo "Dijkstra's Algorithm"
echo "Sequential"
echo "Nodes: Time(Real | User | Sys):"
for file in $(seq 1 3)
do
    #command line params -> ./dijkstras.out fileNumber(1->3): number of threads: enable threads 0 no 1 yes
    line=$(head -1 routes$file.txt)
    timeOutput=$( { time ./dijkstra.out $file 1 0 > /dev/null; } 2>&1)
    echo "$line    $timeOutput"
done
#parallel
echo "Parallel"
echo "Nodes: Threads: Time(Real | User | Sys):"
for file in $(seq 1 3)
do
    #command line params -> ./dijkstras.out fileNumber(1->3): number of threads: enable threads 0 no 1 yes
    line=$(head -1 routes$file.txt)
    timeOutput=$( { time ./dijkstra.out $file 5 1 > /dev/null; } 2>&1)
    echo "$line    5   ($timeOutput)"
done
for file in $(seq 1 3)
do
    #command line params -> ./dijkstras.out fileNumber(1->3): number of threads: enable threads 0 no 1 yes
    line=$(head -1 routes$file.txt)
    timeOutput=$( { time ./dijkstra.out $file 8 1 > /dev/null; } 2>&1)
    echo "$line    8   ($timeOutput)"
done
#Riemann Sums testing-------------------------------------------------------------------------------
#sequential
echo ""
echo "STARTING RIEMANN SUMS APPROXIMATIONS"
echo ""
echo "Riemann Sums LHS"
echo "Sequential"
echo "Starting X: Ending X: Rectangles: Time(Real | User | Sys):"
echo ""
#starting x value
let x_a=0
#ending x value
let x_b=4
#number of rectangles
let n=5
#first run with original values
timeOutput=$( { time ./riemann.out $x_a $x_b $n 1 0 > /dev/null; } 2>&1)
echo "$x_a $x_b    $n  ($timeOutput)"
for count in $(seq 1 3)
do
    let x_b=(x_b+count)*2
    let n=(n+count)*count*2
    #command line params -> ./riemann.out start x: end x: rectangles: number of threads: enable threads 0 no 1 yes
    timeOutput=$( { time ./riemann.out $x_a $x_b $n 1 0 > /dev/null; } 2>&1)
    echo "$x_a $x_b    $n  ($timeOutput)"
done
echo "Parallel"
echo "Starting X: Ending X: Rectangles: Threads: Time(Real | User | Sys):"
echo ""
#starting x value
let x_a=0
#ending x value
let x_b=4
#number of rectangles
let n=5
#first run with original values
timeOutput=$( { time ./riemann.out $x_a $x_b $n 5 1 > /dev/null; } 2>&1)
echo "$x_a $x_b    $n  5   ($timeOutput)"
for count in $(seq 1 3)
do
    let x_b=(x_b+count)*2
    let n=(n+count)*count*2
    #command line params -> ./riemann.out start x: end x: rectangles: number of threads: enable threads 0 no 1 yes
    timeOutput=$( { time ./riemann.out $x_a $x_b $n 5 1 > /dev/null; } 2>&1)
    echo "$x_a $x_b    $n  5   ($timeOutput)"
done
#starting x value
let x_a=0
#ending x value
let x_b=4
#number of rectangles
let n=5
#first run with original values
timeOutput=$( { time ./riemann.out $x_a $x_b $n 8 1 > /dev/null; } 2>&1)
echo "$x_a $x_b    $n  8   ($timeOutput)"
for count in $(seq 1 3)
do
    let x_b=(x_b+count)*2
    let n=(n+count)*count*2
    #command line params -> ./riemann.out start x: end x: rectangles: number of threads: enable threads 0 no 1 yes
    timeOutput=$( { time ./riemann.out $x_a $x_b $n 8 1 > /dev/null; } 2>&1)
    echo "$x_a $x_b    $n  8   ($timeOutput)"
done
echo "All Done!"
