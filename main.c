#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "src/functions.h"


void print_help(void);

//=======================//
// Help message function //
//=======================//

void print_help(void) {
    printf("Usage: ./main [options]\n");
    printf("Options:\n");
    printf("  --help, -help     Print this help message and exit.\n");
    printf("  --root, -r        Print the root results (result1, result2, result3) and exit.\n");
    printf("  --iterations, -i  Print the number of iterations for each root calculation and exit.\n");
    printf("  --test-root, -R   Test the root function with specified parameters (F1:F2:A:B:E:R).\n");
    printf("  --test-integral, -I Test the integral function with specified parameters (F:A:B:E:R).\n");
}

//=================//
// Main function   //
//=================//

int main(int argc, char *argv[]) {
    // Variable declarations
    double a, b, eps;
    root_result_t result1, result2, result3;
    double integral1, integral2, integral3;
    double ans, expected;
    char flag = 1;

    //-----------------------------//
    // Command-line argument check //
    //----------------------------//

    if (argc > 1 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        print_help();
        return 0;
    }

    int print_roots = 0;
    if (argc > 1 && (strcmp(argv[1], "--root") == 0 || strcmp(argv[1], "-r") == 0)) {
        print_roots = 1;
        flag = 0;
    }

    // Check for iterations print request
    int print_iterations = 0;
    if (argc > 1 && (strcmp(argv[1], "--iterations") == 0 || strcmp(argv[1], "-i") == 0)) {
        print_iterations = 1;
        flag = 0;
    }

    // Check for test-root request
    if (argc > 1 && (strcmp(argv[1], "--test-root") == 0 || strcmp(argv[1], "-R") == 0)) {
        if (argc < 3) {
            fprintf(stderr, "Error: Missing parameter for --test-root\n");
            return 1;
        }
        flag = 0;
        // Parse the parameter string
        char *param = argv[2];
        int F1, F2;
        double A, B, E, R;
        if (sscanf(param, "%d:%d:%lf:%lf:%lf:%lf", &F1, &F2, &A, &B, &E, &R) != 6) {
            fprintf(stderr, "Error: Invalid parameter format for --test-root\n");
            return 1;
        }

        // Select the functions based on F1 and F2
        func_t func1, func2;
        switch (F1) {
            case 1: func1 = f1; break;
            case 2: func1 = f2; break;
            case 3: func1 = f3; break;
            default:
                fprintf(stderr, "Error: Invalid function number F1\n");
                return 1;
        }
        switch (F2) {
            case 1: func2 = f1; break;
            case 2: func2 = f2; break;
            case 3: func2 = f3; break;
            default:
                fprintf(stderr, "Error: Invalid function number F2\n");
                return 1;
        }

        // Call the root function with the specified parameters
        root_result_t result = root(func1, func2, A, B, E);

        // Calculate absolute and relative errors
        double absolute_error = fabs(result.root - R);
        double relative_error = absolute_error / fabs(R);

        // Print the results
        printf("Calculated root: %f\n", result.root);
        printf("Expected root: %f\n", R);
        printf("Absolute error: %f\n", absolute_error);
        printf("Relative error: %f\n", relative_error);
        return 0;
    }

    // Check for test-integral request
    if (argc > 1 && (strcmp(argv[1], "--test-integral") == 0 || strcmp(argv[1], "-I") == 0)) {
        if (argc < 3) {
            fprintf(stderr, "Error: Missing parameter for --test-integral\n");
            return 1;
        }
        flag = 0;
        // Parse the parameter string
        char *param = argv[2];
        int F;
        double A, B, E, R;
        if (sscanf(param, "%d:%lf:%lf:%lf:%lf", &F, &A, &B, &E, &R) != 5) {
            fprintf(stderr, "Error: Invalid parameter format for --test-integral\n");
            return 1;
        }

        // Select the function based on F
        func_t func;
        switch (F) {
            case 1: func = f1; break;
            case 2: func = f2; break;
            case 3: func = f3; break;
            default:
                fprintf(stderr, "Error: Invalid function number F\n");
                return 1;
        }

        // Call the integral function with the specified parameters
        double integral_result = integral(func, A, B, E);

        // Calculate absolute and relative errors
        double absolute_error = fabs(integral_result - R);
        double relative_error = absolute_error / fabs(R);

        // Print the results
        printf("Calculated integral: %f\n", integral_result);
        printf("Expected integral: %f\n", R);
        printf("Absolute error: %f\n", absolute_error);
        printf("Relative error: %f\n", relative_error);
        return 0;
    }

    // Handle unspecified options
    if ((argc > 1) && (flag)) {
        fprintf(stderr, "Error: Unrecognized option '%s'\n", argv[1]);
        print_help();
        return 1;
    }

    //---------------------//
    // Perform calculation //
    //--------------------//

    // Setting initial parameters and calculate first result
    a = 2;
    b = 3;
    eps = 1e-5;
    result1 = root(f1, f2, a, b, eps);

    // Setting parameters for second calculation
    a = 1;
    b = 2;
    result2 = root(f2, f3, a, b, eps);

    // Setting parameters for third calculation
    a = 0.2;
    b = 0.5;
    result3 = root(f1, f3, a, b, eps);

    //-----------------------------------------//
    // Handle specific command-line arguments //
    //----------------------------------------//

    // If roots requested, print them
    if (print_roots) {
        printf("The abscissa of the intersection point of exp(-x) + 3 and 2x - 2: %f\n", result1.root);
        printf("The abscissa of the intersection point of 2x - 2 and 1/x: %f\n", result2.root);
        printf("The abscissa of the intersection point of exp(-x) + 3 and 1/x: %f\n", result3.root);
        return 0;
    }

    // If iterations requested, print them
    if (print_iterations) {
        printf("Iterations for Result1: %d\n", result1.iterations);
        printf("Iterations for Result2: %d\n", result2.iterations);
        printf("Iterations for Result3: %d\n", result3.iterations);
        return 0;
    }

    //-------------------------------------//
    // Calculation of integrals and Result //
    //-------------------------------------//

    // Setting precision for integral calculation
    eps = 1e-3;

    // Perform integral calculations
    integral1 = integral(f1, result3.root, result1.root, eps);
    integral2 = integral(f2, result2.root, result1.root, eps);
    integral3 = integral(f3, result3.root, result2.root, eps);

    // Calculate final answer and compare with expected value
    ans = integral1 - integral2 - integral3;
    expected = 3.63579;

    // Check if the result is within the acceptable range
    eps = 0.001;
    if (fabs(ans - expected) < eps) {
        printf("Answer: %f\n", ans);
        printf("Expected: %f with epsilon: %f\n", expected, eps);
        printf("Success!\n");
    } else {
        printf("Received: %f; Expected: %f :c\n", ans, expected);
    }

    return 0;
}
