#include "functions.h"

//==============================//
// Root-finding function        //
//==============================//

// Function to find the root of f(x) = g(x) using the Secant Method
// Takes two functions f and g, interval [a, b], and precision eps1
root_result_t root(func_t f, func_t g, double a, double b, double eps1) {
    int iterations = 0; // Initialize iteration counter
    double x0 = a;      // Initial guess x0
    double x1 = b;      // Initial guess x1
    double x2;          // Variable to store the new approximation

    // Iterate until the difference between x1 and x0 is less than eps1
    while (fabs(x1 - x0) > eps1) {
        double fx0 = f(x0) - g(x0);
        double fx1 = f(x1) - g(x1);
        x2 = x1 - (fx1 * (x1 - x0)) / (fx1 - fx0);
        x0 = x1;
        x1 = x2;
        iterations++;
    }

    // Store the result in a root_result_t structure
    root_result_t result = { .root = x1, .iterations = iterations };
    return result;
}

//===============================//
// Integral calculation function //
//===============================//

// Function to calculate the integral of f over [a, b] using Simpson's method
// Takes a function f, interval [a, b], and precision eps2
double integral(func_t f, double a, double b, double eps2) {
    int n = 40; // Analytically obtained that the required accuracy is achieved at n = 20,11135. Because n is an integer, let's take n = 40
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    //double integral_old = 0.0; 
    double integral_new = 0.0;

    // Initial integral value computation using Simpson's rule
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0) {
            sum += 2 * f(x); // 2 * f(x) for even i
        } else {
            sum += 4 * f(x); // 4 * f(x) for odd i
        }
    }
    integral_new = (h / 3) * sum; // Compute the initial integral value

    /*
    // Refine the integral value until the desired precision is achieved
    do {
        integral_old = integral_new;
        n *= 2;
        h = (b - a) / n;
        sum = f(a) + f(b);

        // Recompute the integral value using Simpson's rule
        for (int i = 1; i < n; i++) {
            double x = a + i * h;
            if (i % 2 == 0) {
                sum += 2 * f(x);
            } else {
                sum += 4 * f(x);
            }
        }
        integral_new = (h / 3) * sum;
    } while (fabs(integral_new - integral_old) > eps2); // Check precision
    */
    return integral_new;
}
