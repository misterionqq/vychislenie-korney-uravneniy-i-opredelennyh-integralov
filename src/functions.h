#ifndef HEADER_GUARD_INTEGRAL_H_INCLUDED
#define HEADER_GUARD_INTEGRAL_H_INCLUDED

//==============================//
// Included standard libraries  //
//==============================//

#include <stdio.h>
#include <math.h>

//==============================//
// Type definitions             //
//==============================//

// Function type which takes and returns a double
typedef double (*func_t)(double);

// Structure to store the result of the root-finding function
typedef struct {
    double root;       // The root value
    int iterations;    // The number of iterations taken to find the root
} root_result_t;

//==============================//
// Function prototypes          //
//==============================//

// Prototypes for the mathematical functions
double f1(double x);
double f2(double x);
double f3(double x);

// Prototype for the root-finding function (using the secant method)
// Takes two functions f and g, interval [a, b], and precision eps
root_result_t root(func_t f, func_t g, double a, double b, double eps);

// Prototype for the integral calculation function (using the Simpson's method)
// Takes a function f, interval [a, b], and precision eps2
double integral(func_t f, double a, double b, double eps2);

#endif // HEADER_GUARD_INTEGRAL_H_INCLUDED