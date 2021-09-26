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
    STATUS status;
    double real;
    double im;
};


int main() {
    UnitTest("./Squared/squared_tests.txt");
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

    NUM_ROOTS n_roots = SolveSquared(&data_a, &data_b, &data_c, &x1, &x2);
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
NUM_ROOTS SolveLinear(struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x) {
    NUM_ROOTS n_roots = ERROR_ROOTS;
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
NUM_ROOTS FindSquareRoots(struct exp_data* data_a, struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x1, struct compl_num* x2) {
    // a != 0 guaranteed from parent function
    NUM_ROOTS n_roots = ERROR_ROOTS;

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
NUM_ROOTS SolveSquared(struct exp_data* data_a, struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x1, struct compl_num* x2) {
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

    NUM_ROOTS n_roots = ERROR_ROOTS;

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
int PrintResult(NUM_ROOTS n_roots, struct compl_num* x1, struct compl_num* x2) {
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
        printf("You can't request to read zero arguments.\n");
        return -1;
    } else {
        if (n_scanned == n_needed) {
            return 0;
        } else {
            printf("Number of read arguments is %d, not equal to number needed.\n", n_scanned);
            return -1;
        }
    }
}

// Defining Unit Test function
TEST_RESULTS TestOneRoot (FILE* tests, STATUS status_test, struct compl_num* x1) {

    TEST_RESULTS result = TEST_ERROR;
    struct compl_num x1_test = {ERROR_STATUS, NAN, NAN};
    ScanCheck(1, fscanf(tests, "%lg", &(x1_test.real)));
    if ((status_test != x1->status) || (x1->status != REAL)) {
        printf("Wrong root status.\n");
        return TEST_ERROR;
    }
    if ((x1->real == x1_test.real)) {
        result = PASSED;
    } else {
        result = NOT_PASSED;
    }
    return result;
}

TEST_RESULTS TestTwoRoots (FILE* tests, STATUS status_test, struct compl_num* x1, struct compl_num* x2) {
    TEST_RESULTS result = TEST_ERROR;

    struct compl_num x1_test = {ERROR_STATUS, NAN, NAN};
    struct compl_num x2_test = {ERROR_STATUS, NAN, NAN};

    // it is always 2 roots
    if ((x1->status == status_test) && (x2->status == status_test)) {
        switch(status_test) {
            case REAL:
                ScanCheck(2, fscanf(tests, "%lg %lg", &(x1_test.real), &(x2_test.real)));
                if ((x1->real == x1_test.real) && (x2->real == x2_test.real)) {
                    result = PASSED;
                } else {
                    result = NOT_PASSED;
                }
                break;

            case IMAGINARY:
                ScanCheck(2, fscanf(tests, "%lgi %lgi", &(x1_test.im), &(x2_test.im)));
                if ((x1->im == x1_test.im) && (x2->im == x2_test.im)) {
                    result = PASSED;
                } else {
                    result = NOT_PASSED;
                    }
                break;

            case COMPLEX:
                ScanCheck(4, fscanf(tests, "%lg %lgi, %lg %lgi", &(x1_test.real), &(x1_test.im), &(x2_test.real), &(x2_test.im)));
                printf("Read roots: %lg %lgi, %lg %lgi\n", x1_test.real, x1_test.im, x2_test.real, x2_test.im);

                if ((x1->real == x1_test.real) && (x2->real == x2_test.real) && (x1->im == x1_test.im) && (x2->im == x2_test.im)) {
                    result = PASSED;
                } else {
                    result = NOT_PASSED;
                }
                break;
            // нет default, потому что он не должен ничего делать
        }
    }
    return result;
}

int UnitTest (char path[]) {
    TEST_RESULTS result = TEST_ERROR;

    FILE* tests = NULL;
    tests = fopen(path, "r");
    if (tests == NULL) {
        printf("Cannot open file with tests.\n");
        return 0;
    }
    int n_tests;
    ScanCheck(1, fscanf(tests, "%d", &n_tests));
    printf("n_tests = %d\n", n_tests);

    TEST_RESULTS test_results[n_tests];
    struct exp_data data_a = {NAN, NAN};
    struct exp_data data_b = {NAN, NAN};
    struct exp_data data_c = {NAN, NAN};
    struct compl_num x1 = {ERROR_STATUS, NAN, NAN};
    struct compl_num x2 = {ERROR_STATUS, NAN, NAN};

    NUM_ROOTS n_roots_test = ERROR_ROOTS;
    STATUS status_test = ERROR_STATUS;

    for (int i = 1; i <= n_tests; ++i) {


        // Reading input and number of roots
        ScanCheck(3, fscanf(tests, "%lg %lg %lg", &(data_a.value), &(data_b.value), &(data_c.value)));
        printf("values = %lg %lg %lg\n", data_a.value, data_b.value, data_c.value);
        ScanCheck(3, fscanf(tests, "%lg %lg %lg", &(data_a.sigma), &(data_b.sigma), &(data_c.sigma)));
        printf("margins = %lg %lg %lg\n", data_a.sigma, data_b.sigma, data_c.sigma);
        ScanCheck(1, fscanf(tests, "%d", &n_roots_test));
        printf("n_roots_test = %d\n", n_roots_test);

        // Solving equation
        NUM_ROOTS n_roots = SolveSquared(&data_a, &data_b, &data_c, &x1, &x2);

        if ((n_roots == n_roots_test)) {
            if ((n_roots_test == INF_ROOTS) || n_roots_test == NO_ROOTS) {
                result = PASSED;
            } else {
                ScanCheck(1, fscanf(tests, "%d", &status_test));
                printf("status_test = %d\n", status_test);

                switch (n_roots_test) {
                    case ONE_ROOT:
                        result = TestOneRoot(tests, status_test, &x1);
                        break;

                    case TWO_ROOTS:
                        result = TestTwoRoots(tests, status_test, &x1, &x2);
                        break;

                    default:
                        printf("Wrong number of roots read in tests: %d.\n", n_roots_test);
                        return -1;
                }
            }
        } else {
            printf ("Wrong number of roots.\n");
            result = TEST_ERROR;
        }

        printf("Test number %d: result code %d\n", i, result);

        exp_data data_a = {NAN, NAN};
        exp_data data_b = {NAN, NAN};
        exp_data data_c = {NAN, NAN};
        compl_num x1 = {ERROR_STATUS, NAN, NAN};
        compl_num x2 = {ERROR_STATUS, NAN, NAN};

        n_roots_test = ERROR_ROOTS;
        status_test = ERROR_STATUS;
    }
    return 0;
}
