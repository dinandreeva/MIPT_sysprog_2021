/*! \file header.h
    \brief Заголовочный файл с документацией по квадратному уравнению.
*/

// Определение enum'ов

/// \brief enum для числа корней.
typedef enum {
    INF_ROOTS = -1,
    NO_ROOTS  =  0,
    ONE_ROOT  =  1,
    TWO_ROOTS =  2,
    ERROR_ROOTS = -10
} NUM_ROOTS;


/*! \brief enum для типа погрешности.

    Данный тип помогает различать типы погрешностей. Вычисляются
    погрешности дискриминанта и вещественной части корней уравнения.
*/
typedef enum {
    D = 1,
    B_DIVIDE_2A = 0
} MARGIN_TYPE;


/*! \brief enum для типа комплексного числа.

    Данный тип содержит в себе информацию о том есть ли у
    комплексного числа вещественная или мнимая части.
*/
typedef enum {
    REAL = 1,
    IMAGINARY = -1,
    COMPLEX = 0,
    ERROR_STATUS = -10
} STATUS;


/*! \brief enum для результата юнит-тестирования.

    Данный тип информирует о результатах юнит-тестирования, а также
    сообщает тип ошибки в тесте.
*/
typedef enum {
    PASSED = 0,
    NOT_PASSED = 1,
    TEST_ERROR = -1,
    TEST_N_ROOT_ERROR = -2,
    TEST_FILE_ERROR = -3,
    TEST_START_VALUE = 2
} TEST_RESULTS;


/// \brief Cтруктура для совместного хранения величины и её погрешности.
struct exp_data {
    double value;
    double sigma;
};


/// \brief Структура для хранения данных комплексных чисел.
struct compl_num {
    STATUS status;
    double real;
    double im;
};


/*! \brief Вычисление погрешности действительной части корней квадратного уравнения.
    \param a, b Два указателя на структуры для хранения данных.

    \return Значение вычисленной погрешности.
*/
double CalcErrorBDividedBy2A(struct exp_data* a, struct exp_data* b);


/*! \brief Вычисление погрешности дискриминанта.
    \param a, b, c Три указателя на структуры для хранения данных.

    \return Значение вычисленной погрешности.
*/
double CalcErrorD(struct exp_data* a, struct exp_data* b, struct exp_data* c);


/*! \brief Ассёрт на количество считанных аргументов из стандартного ввода.
    \param n_needed Сколько аргументов нужно.
    \param n_scanned Сколько аргументов прочитано.
*/
int AssertScan(int n_needed, int n_scanned);


/*! \brief Приблизительное равно.
    \param val1, val2 Значения сравниваемых чисел.
    \param sigma Значение погрешности сравнения.

    \return Результат логической арифметики.
*/
int AlmostEquals(double val1, double val2, double sigma);


/*! \brief Уравнивание с округлением до разряда N.
    \param val1, val2 Значения сравниваемых чисел.
    \param n Положительное число разрядов.

    \return Результат логической арифметики.
*/
int EqualsTillN(double val1, double val2, int n);


/*! \brief Уравнивание комплексных чисел с округлением до разряда N.
    \param cn1, cn2 Указатели на сравниваемые числа.
    \param n Положительное число разрядов.

    \return Результат логической арифметики.
*/
int EqualsComplexTillN (struct compl_num* cn1, struct compl_num* cn2, int n);



/*! \brief Решатель линейного уравнения.
    \param data_b, data_c Указатели на структуры с коэффициентами b и c.
    \param x Указатель на корень в родительской функции.

    \return Количество корней типа NUM_ROOTS.
*/
NUM_ROOTS SolveLinear(struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x);


/*! \brief Вычислитель корней квадратного уравнения.
    \param data_a, data_b, data_c Указатели на структуры с коэффициентами a, b и c.
    \param x1, x2 Указатели на корни в родительской функции.

    \return Количество корней типа NUM_ROOTS.
*/
NUM_ROOTS FindSquareRoots(struct exp_data* data_a, struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x1, struct compl_num* x2);


/*! \brief Решатель строго квадратного уравнения.
    \param data_a, data_b, data_c Указатели на структуры с коэффициентами a, b и c.
    \param x1, x2 Указатели на корни в родительской функции.

    \return Количество корней типа NUM_ROOTS.
*/
NUM_ROOTS SolveSquared(struct exp_data* data_a, struct exp_data* data_b, struct exp_data* data_c, struct compl_num* x1, struct compl_num* x2);


/*! \brief Конвертация -0.0 в 0.0
    \param number Число с плавающей точкой.

    \return Исправленное число с плавающей точкой.
*/
float PlusZeroNum (float n);

/*! \brief Печать комплексного числа.
    \param number Указатель на комплексное число.
*/
int PrintComplexNum(struct compl_num* number);


/*! \brief Печать ответа.
    \param n_roots Количество корней.
    \param x1, x2 Указатели на полученные корни уравнения.
*/
int PrintResult(NUM_ROOTS n_roots, struct compl_num* x1, struct compl_num* x2);



// Функции для юнит тестов
/*! \brief Сравнение решения линейного уравнения с ответом теста.
    \param tests Указатель на поток с тестами.
    \param status_test Тип комплексного числа корня, прочитанный из теста.
    \param x1 Указатель на корень.
    \param N Разряд до которого округлять.

    \return Результат теста.
*/
TEST_RESULTS TestOneRoot (FILE* tests, STATUS status_test, struct compl_num* x1, int N);


/*! \brief Сравнение решения строго квадратного уравнения с ответом теста.
    \param tests Указатель на поток с тестами.
    \param status_test Тип комплексного числа корней, прочитанный из теста.
    \param x1, x2 Указатели на корни.
    \param N Разряд до которого округлять.

    \return Результат теста.
*/
TEST_RESULTS TestTwoRoots (FILE* tests, STATUS status_test, struct compl_num* x1, struct compl_num* x2, int N);


/*! \brief Юнит-тестирование
    \param path Путь к файлу с тестами.
    \param N Разряд до которого округлять.

    \return Результат теста.
*/
int UnitTest (const char* path, int N);
