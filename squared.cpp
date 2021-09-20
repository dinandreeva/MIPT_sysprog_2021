#include <stdio.h>
#include <math.h>
#include <assert.h>

enum NUM_ROOTS {
    INF_ROOTS = -1,
    NO_ROOTS  =  0,
    ONE_ROOT  =  1,
    TWO_ROOTS =  2,
    ERROR_ROOTS = -10
};

enum STATUS {
        REAL = 1,
        IMAGINARY = -1,
        COMPLEX = 0,
        ERROR_STATUS = -10
};

// Calculating errors
enum MARGIN_TYPE {
    D = 1,
    B_DIVIDE_2A = 0
};

// Experimental data
struct exp_data {
    double value;
    double sigma;
};

struct compl_num {
    enum STATUS status;
    double real;
    double im;

};

double CalcErrorBDividedBy2A(struct exp_data* a, struct exp_data* b) {
    return sqrt(pow(b->sigma, 2) + pow(b->value * a->sigma / a->value, 2)) / (2 * a->value);
}

double CalcErrorD(struct exp_data* a, struct exp_data* b, struct exp_data* c) {
    return 2 * sqrt(pow(b->value * b->sigma, 2) + 4 * (pow(c->value * a->sigma, 2) + pow(a->value, c->sigma)));
}

int AlmostEquals(double val1, double val2, double sigma) {
    return (val1 + sigma >= val2) && (val1 - sigma <= val2);
}

int PrintComplexNum(struct compl_num* num) {
    switch(num->status) {
        case REAL:
            printf("%lg", num->real);
            break;
        case IMAGINARY:
            printf("%lgi", num->im);
            break;
        case COMPLEX:
            printf("%lg + %lgi", num->real, num->im);
            break;
        default:
            printf("Error in PrintComplexNum!\n"
                   "num->status = %d", num->status);
            return -1;
    }
    return 0;
}



int SolveLinear(enum NUM_ROOTS* p_n_roots, struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x) {
    double b = data_b->value;
    double c = data_c->value;
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x != NULL);

    if (AlmostEquals(b, 0, data_b->sigma)) {
        if (AlmostEquals(c, 0, data_c->sigma)) {
            *p_n_roots = INF_ROOTS;
        }
        else {
            *p_n_roots = NO_ROOTS;
        }
    } 
    else {
        x->status = REAL;
        x->real = - c / b;
        x->im = 0;
        *p_n_roots = ONE_ROOT;
    }
    return 0;
}

int FindSquareRoots(double d, struct exp_data* data_a, struct exp_data* data_b, struct compl_num* x1, struct compl_num* x2) {
    double b = data_b->value;
    double a = data_a->value;

    if (d > 0) {
        double sqrt_d = sqrt(d);

        x1->status = x2->status = REAL;

        x1->real = - b + sqrt_d / (2 * a);
        x1->im = 0;

        x2->real = - b - sqrt_d / (2 * a);
        x1->im = 0;

        return 0;

    } else {  // is_im == 1
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

        return 0;
    }
}

enum NUM_ROOTS SolveSquared(struct exp_data* data_a, struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x1, struct compl_num* x2) 
{

    // checking the inputs
    // std remove
    assert(data_a != NULL);
    assert(data_b != NULL);
    assert(data_c != NULL);

    double a = data_a->value;
    double b = data_b->value;
    double c = data_c->value;

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);


    enum NUM_ROOTS n_roots = ERROR_ROOTS;
    enum NUM_ROOTS* p_n_roots = &n_roots;

    if (AlmostEquals(data_a->value, 0, data_a->sigma)) {
        SolveLinear(p_n_roots, data_b, data_c, x1);
    } else {	
        double d = 0;
        d = pow(b, 2) - 4 * a * c;
        if (AlmostEquals(d, 0, CalcErrorD(data_a, data_b, data_c))) {
            x1->real = x2->real = - b / (2 * a); // a <> 0
            x1->status = x2->status = REAL;
            n_roots = ONE_ROOT;
        } else {
            n_roots = TWO_ROOTS;
            FindSquareRoots(d, data_a, data_b, x1, x2);
        }
	}
    return n_roots;
}

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

int main() {

    printf("Solve square equation\n"
           "Input a, b, c:\n");

    // Initializing variables
    struct exp_data data_a_val = {NAN, NAN};
    struct exp_data data_b_val = {NAN, NAN};
    struct exp_data data_c_val = {NAN, NAN};
    struct compl_num x1_val = {ERROR_STATUS, NAN, NAN};
    struct compl_num x2_val = {ERROR_STATUS, NAN, NAN};

    struct exp_data* data_a = &data_a_val;
    struct exp_data* data_b = &data_b_val;
    struct exp_data* data_c = &data_c_val;
    struct compl_num* x1 = &x1_val;
    struct compl_num* x2 = &x2_val;

    scanf("%lg %lg %lg", &(data_a_val.value), &(data_b_val.value), &(data_c_val.value));

    printf("Input error margins:\n");

    scanf("%lg %lg %lg", &(data_a_val.sigma), &(data_b_val.sigma), &(data_c_val.sigma));

//	double a  = NAN, b  = NAN, c = NAN;
//	double x1 = NAN, x2 = NAN;


    enum NUM_ROOTS n_roots = SolveSquared(data_a, data_b, data_c, x1, x2);
    PrintResult(n_roots, x1, x2);
    return 0;
}
