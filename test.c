#include "src/functions.h"

// Function prototypes
double _f1(double x);
double _f2(double x);
double _f3(double x);

//==================================//
// Mathematical functions for tests //
//==================================//

double _f1(double x) {
    // Function equation x^2 - 4
    return x * x - 4;
}

double _f2(double x) {
    // Function equation sin(x)
    return sin(x);
}

double _f3(double x) {
    // Function equation 5 - 2/x
    return 5 - 2 / x;
}

//==================//
// Test function    //
//==================//

int main(void) {
    printf("TEST OF ROOTS:\n");

    //---------------------//
    // Root calculations   //
    //---------------------//

    root_result_t result1 = root(_f1, _f2, 2, 3, 1e-6);
    double expected1 = 2.193673;

    if (fabs(result1.root - expected1) < 1e-6) {
        printf("TEST 1: OK\n");
    } else printf("TEST 1: FAILED (received: %f, expected: %f)\n", result1.root, expected1);

    root_result_t result2 = root(_f2, _f3, 0.3, 0.5, 1e-6);
    double expected2 = 0.436988;

    if (fabs(result2.root - expected2) < 1e-6) {
        printf("TEST 2: OK\n");
    } else printf("TEST 2: FAILED (received: %f, expected: %f)\n", result2.root, expected2);

    root_result_t result3 = root(_f1, _f3, 2, 3, 1e-6);
    double expected3 = 2.882021;

    if (fabs(result3.root - expected3) < 1e-6) {
        printf("TEST 3: OK\n");
    } else printf("TEST 3: FAILED (received: %f, expected: %f)\n", result3.root, expected3);

    printf("----------------------------------\n");
    printf("TEST OF INTEGRALS:\n");

    //-----------------------//
    // Integral calculations //
    //-----------------------//

    double integral1 = integral(_f1, 2, 3, 1e-6);
    expected1 = 2.333333;

    if (fabs(integral1 - expected1) < 1e-6) {
        printf("TEST 1: OK\n");
    } else printf("TEST 1: FAILED (received: %f, expected: %f)\n", integral1, expected1);

    double integral2 = integral(_f2, 0, 1, 1e-6);
    expected2 = 0.459698;

    if (fabs(integral2 - expected2) < 1e-6) {
        printf("TEST 2: OK\n");
    } else printf("TEST 2: FAILED (received: %f, expected: %f)\n", integral2, expected2);

    double integral3 = integral(_f3, 1, 2, 1e-6);
    expected3 = 3.613706;

    if (fabs(integral3 - expected3) < 1e-6) {
        printf("TEST 3: OK\n");
    } else printf("TEST 3: FAILED (received: %f, expected: %f)\n", integral3, expected3);
}