#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "header.h"

// Defining struct for experimental data with error margins
struct exp_data {
    double value;
    double sigma;
};


// Defining complex number

// Defining complex number structure
struct compl_num {
    enum STATUS status;
    double real;
    double im;
};


int main() {

    printf("Solve square equation\n"
           "Input a, b, c:\n");

    // Initializing variables
    struct exp_data data_a = {NAN, NAN};
    struct exp_data data_b = {NAN, NAN};
    struct exp_data data_c = {NAN, NAN};
    struct compl_num x1 = {ERROR_STATUS, NAN, NAN};
    struct compl_num x2 = {ERROR_STATUS, NAN, NAN};

    ScanCheck(3, scanf("%lg %lg %lg", &(data_a.value), &(data_b.value), &(data_c.value)));

    printf("Input error margins:\n");

    ScanCheck(3, scanf("%lg %lg %lg", &(data_a.sigma), &(data_b.sigma), &(data_c.sigma)));

    enum NUM_ROOTS n_roots = SolveSquared(&data_a, &data_b, &data_c, &x1, &x2);
    PrintResult(n_roots, &x1, &x2);

    return 0;
}

// Defining functions

// Functions for error calcucation
double CalcErrorBDividedBy2A(struct exp_data* a, struct exp_data* b) {
    // printf("Error -B/2a: %lg\n", sqrt(pow(b->sigma, 2) + pow(b->value * a->sigma / a->value, 2)) / (2 * a->value));
    return sqrt(pow(b->sigma, 2) + pow(b->value * a->sigma / a->value, 2)) / (2 * a->value);
}

double CalcErrorD(struct exp_data* a, struct exp_data* b, struct exp_data* c) {
    // printf("Error D: %lg\n", 2 * sqrt(pow(b->value * b->sigma, 2) + 4 * (pow(c->value * a->sigma, 2) + pow(a->value, c->sigma))));
    return 2 * sqrt(pow(b->value * b->sigma, 2) + 4 * (pow(c->value * a->sigma, 2) + pow(a->value * c->sigma, 2)));
}


// Function for equality taking in mind error
int AlmostEquals(double val1, double val2, double sigma) {
    // printf("Almost equals: %d\n", (val1 + sigma >= val2) && (val1 - sigma <= val2));
    return (val1 + sigma >= val2) && (val1 - sigma <= val2);
}


// Defining functions for solving equation

// Function for solving linear equation
enum NUM_ROOTS SolveLinear(struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x) {
    enum NUM_ROOTS n_roots = ERROR_ROOTS;
    double b = data_b->value;
    double c = data_c->value;
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x != NULL);

    if (AlmostEquals(b, 0, data_b->sigma)) {
        if (AlmostEquals(c, 0, data_c->sigma)) {
            n_roots = INF_ROOTS;
        }
        else {
            n_roots = NO_ROOTS;
        }
    }
    else {
        x->status = REAL;
        x->real = - c / b;
        x->im = 0;
        n_roots = ONE_ROOT;
    }
    return n_roots;
}

// Function for finding square roots
enum NUM_ROOTS FindSquareRoots(struct exp_data* data_a, struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x1, struct compl_num* x2) {
    // a != 0 guaranteed from parent function
    enum NUM_ROOTS n_roots = ERROR_ROOTS;

    double a = data_a->value;
    double b = data_b->value;
    double c = data_c->value;

    // Calculating discriminant
    double d = pow(b, 2) - 4 * a * c;
    if (AlmostEquals(d, 0, CalcErrorD(data_a, data_b, data_c))) {
        n_roots = ONE_ROOT;
        x1->real = x2->real = - b / (2 * a);  // a != 0
        x1->status = x2->status = REAL;
    } else {
        n_roots = TWO_ROOTS;
        if (d > 0) {
            double sqrt_d = sqrt(d);

            x1->status = x2->status = REAL;
            x1->real = - b + sqrt_d / (2 * a);
            x1->im = 0;
            x2->real = - b - sqrt_d / (2 * a);
            x1->im = 0;
        } else {  // Complex roots
            double sqrt_d = sqrt(-d);

            if (AlmostEquals(- b / (2 * a), 0, CalcErrorBDividedBy2A(data_a, data_b))) {
                x1->status = x2->status = IMAGINARY;
                x1->real = x2->real = 0;
            } else {
                x1->real = x2->real = -b / (2 * a);
                x1->status = x2->status = COMPLEX;
            }

            x1->im = sqrt_d / (2 * a);
            x2->im = -sqrt_d / (2 * a);
        }
    }
    return n_roots;
}

// Function for solving square equation
enum NUM_ROOTS SolveSquared(struct exp_data* data_a, struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x1, struct compl_num* x2) 
{
    // checking the inputs
    assert(data_a != NULL);
    assert(data_b != NULL);
    assert(data_c != NULL);

    assert(isfinite(data_a->value));
    assert(isfinite(data_b->value));
    assert(isfinite(data_c->value));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    enum NUM_ROOTS n_roots = ERROR_ROOTS;

    if (AlmostEquals(data_a->value, 0, data_a->sigma)) {
        n_roots = SolveLinear(data_b, data_c, x1);
    } else {	
        n_roots = FindSquareRoots(data_a, data_b, data_c, x1, x2);
	}
    return n_roots;
}


// Defining functions for printing

// Function for printing complex numbers
int PrintComplexNum(struct compl_num* number) {
    switch(number->status) {
        case REAL:
            printf("%lg", number->real);
            break;
        case IMAGINARY:
            printf("%lgi", number->im);
            break;
        case COMPLEX:
            printf("%lg + %lgi", number->real, number->im);
            break;
        default:
            printf("Error in PrintComplexNum!\n"
                   "num->status = %d", number->status);
            return -1;
    }
    return 0;
}

// Function for printing result
int PrintResult(enum NUM_ROOTS n_roots, struct compl_num* x1, struct compl_num* x2) {
    printf("Roots of the equation: ");
    switch(n_roots) {
        case NO_ROOTS:
            printf("No roots\n");
            break;
        case INF_ROOTS:
            printf("Infinite number of roots\n");
            break;
        case ONE_ROOT:
            printf("One root\n"
                   "x = ");
            PrintComplexNum(x1);
            printf("\n");
            break;
        case TWO_ROOTS:
            if (x1->im > 0) {
                printf("Two roots\n"
                       "x1 = ");
                PrintComplexNum(x1);
                printf("\n"
                       "x2 = ");
                PrintComplexNum(x2);
                printf("\n");
            break;
        }
        default:
            printf("Error in PrintResult!\n"
                    "n_roots = %d\n", n_roots);
            return -1;
    }
    return 0;
}

int ScanCheck(int n_needed, int n_scanned) {
    if (n_needed <= 0) {
        printf("You can't request to read zero arguments.");
        return -1;
    } else {
        if (n_scanned == n_needed) {
            return 0;
        } else {
            printf("Number of read arguments not equal to number needed.");
            return -1;
        }
    }
}

// Defining Unit Test function

int UnitTest(char path[]) {
    FILE *tests;
    tests = fopen(path, "r");
    if (tests == NULL) {
        printf("Cannot open file with tests.\n");
        return 0;
    } else {
        int test_results[100];

        struct exp_data data_a;
        struct exp_data data_b;
        struct exp_data data_c;

        struct compl_num x1;
        struct compl_num x2;

        int n_tests;

        int n_roots;
        char root_type;

        ScanCheck(1, fscanf(tests, "%d", &n_tests));

        for (int i = 0; i < n_tests; ++i) {
            ScanCheck(3, fscanf(tests, "%lg %lg %lg", &(data_a.value), &(data_b.value), &(data_c.value)));
            ScanCheck(3, fscanf(tests, "%lg %lg %lg", &(data_a.sigma), &(data_b.sigma), &(data_c.sigma)));
            ScanCheck(2, fscanf(tests, "%d %c", &n_roots, &root_type));
            // checking roots
        }
    }
    return 0;
}
