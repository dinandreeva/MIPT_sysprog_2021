// Defining enums

// Defining enum for number of roots
typedef enum {
    INF_ROOTS = -1,
    NO_ROOTS  =  0,
    ONE_ROOT  =  1,
    TWO_ROOTS =  2,
    ERROR_ROOTS = -10
} NUM_ROOTS;

// Defining enum for calculating errors
typedef enum {
    D = 1,
    B_DIVIDE_2A = 0
} MARGIN_TYPE;


// Defining enum for complex number marker
typedef enum {
    REAL = 1,
    IMAGINARY = -1,
    COMPLEX = 0,
    ERROR_STATUS = -10
} STATUS;

// Defining enum for test
typedef enum {
    PASSED = 0,
    NOT_PASSED = 1,
    TEST_ERROR = -1
} TEST_RESULTS;

struct exp_data;
struct compl_num;

double CalcErrorBDividedBy2A(struct exp_data* a, struct exp_data* b);
double CalcErrorD(struct exp_data* a, struct exp_data* b, struct exp_data* c);
int AlmostEquals(double val1, double val2, double sigma);
NUM_ROOTS SolveLinear(struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x);
NUM_ROOTS FindSquareRoots(struct exp_data* data_a, struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x1, struct compl_num* x2);
NUM_ROOTS SolveSquared(struct exp_data* data_a, struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x1, struct compl_num* x2);
int PrintComplexNum(struct compl_num* number);
int PrintResult(NUM_ROOTS n_roots, struct compl_num* x1, struct compl_num* x2);
int ScanCheck(int n_needed, int n_scanned);
TEST_RESULTS TestOneRoot (FILE* tests, STATUS status_test, struct compl_num* x1);
TEST_RESULTS TestTwoRoots (FILE* tests, STATUS status_test, struct compl_num* x1, struct compl_num* x2);
int UnitTest (char path[]);
