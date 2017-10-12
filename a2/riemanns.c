#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14159265

/* 
  Define func as a function type that takes 
  a double and returns a double.
*/
typedef double (*func)(double);

/* Calculates the area under a curve */
double area(func, double, double, int);
double square(double);
double trig_sin(double);

int main(int argc, char* argv[]) {
  int a = 1, b = 5;
  int n = 20;
  printf("area of x^2 is %f\n", area(square, a, b, n));
  printf("area of sin is %f\n", area(trig_sin, a, b, n));
  printf("area of e^x is %f\n", area(exp, a, b, n));
  return 0;
}

/* Equavalent to pow(x, 2) */
double square(double x) {
  return x * x;
}

double trig_sin(double x) {
  return sin(x * PI / 180);
}

double area(func f, double a, double b, int n) {
  double deltaX = fabs(a - b) / n;
  double sum = 0.0;
  double x = a;
  #pragma omp parrallel for reduction(+:sum)
  for(int i = 0; i < n; i++) {
    #pragma omp critical
    {
      x += deltaX;
    }

    #pragma omp barrier
    sum += f(x) * deltaX;
  }
  // for (double x = a; x <= b; x += deltaX) {
  //   sum += f(x) * deltaX;
  // }
  return sum;
}