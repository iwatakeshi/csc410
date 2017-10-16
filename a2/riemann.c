#include <math.h>
#include <omp.h>
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
double area_seq(func, double, double, int);
double square(double);
double trig_sin(double);
double trig_2_plus_sin(double);

int main(int argc, char* argv[]) {
  int a = 0, b = 4, n = 5;
  if (argc == 4) {
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    n = atoi(argv[3]);
  }

  printf("a: %d, b: %d, n: %d\n\n", a, b, n);

  printf("area of x^2 is %f\n\n", area(square, a, b, n));
  printf("area of 2 + sin is %f\n\n", area(trig_2_plus_sin, a, b, n));
  printf("area of e^x is %f\n\n", area(exp, a, b, n));
  return 0;
}

/* Equavalent to pow(x, 2) */
double square(double x) {
  return x * x;
}

double trig_sin(double x) {
  return sin(x * PI / 180);
}

double trig_2_plus_sin(double x) {
  return 2.0 + sin(x * PI / 180.0);
}

double sum = 0;

/*Left Riemann Sum */
double area(func f, double a, double b, int n) {

  double x = 0, deltaX = fabs(b - a) / n;
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < n; i++) {
    x = a + i * deltaX;
    sum += f(x) * deltaX;
    // printf("thread id: %d, sum: %f\n", omp_get_thread_num(), sum);
  }

  return sum;
}

/*Left Riemann Sum */
double area_seq(func f, double a, double b, int n) {
  sum = 0;
  double x = 0, deltaX = fabs(b - a) / n;
  for (int i = 0; i < n; i++) {
    x = a + i * deltaX;
    sum += f(x) * deltaX;
  }
  return sum;
}