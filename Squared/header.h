// Defining enums

// Defining enum for number of roots
enum NUM_ROOTS {
    INF_ROOTS = -1,
    NO_ROOTS  =  0,
    ONE_ROOT  =  1,
    TWO_ROOTS =  2,
    ERROR_ROOTS = -10
};

// Defining enum for calculating errors
enum MARGIN_TYPE {
    D = 1,
    B_DIVIDE_2A = 0
};


// Defining enum for complex number marker
enum STATUS {
    REAL = 1,
    IMAGINARY = -1,
    COMPLEX = 0,
    ERROR_STATUS = -10
};

// Defining enum for test
enum TEST_RESULTS {
    PASSED = 0,
    NOT_PASSED = 1,
    ERROR = -1
};

struct exp_data;
struct compl_num;

double CalcErrorBDividedBy2A(struct exp_data* a, struct exp_data* b);
double CalcErrorD(struct exp_data* a, struct exp_data* b, struct exp_data* c);
int AlmostEquals(double val1, double val2, double sigma);
enum NUM_ROOTS SolveLinear(struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x);
enum NUM_ROOTS FindSquareRoots(struct exp_data* data_a, struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x1, struct compl_num* x2);
enum NUM_ROOTS SolveSquared(struct exp_data* data_a, struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x1, struct compl_num* x2);
int PrintComplexNum(struct compl_num* number);
int PrintResult(enum NUM_ROOTS n_roots, struct compl_num* x1, struct compl_num* x2);
int ScanCheck(int n_needed, int n_scanned);
