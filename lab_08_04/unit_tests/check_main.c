#include <check.h>
#include "matrix.h"
#include "userio.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))

START_TEST(test_matrix_mul_unit)
{
    matrix_t unit = { 3, 3 };
    matrix_t result;
    matrix_initialize(&unit.element, 3, 3);
    
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            unit.element[i][j] = i == j;

    exit_t exit_code = matrix_multiply(&unit, &unit, &result);

    ck_assert_int_eq(exit_code, 0);
    ck_assert_int_eq(unit.rows, result.rows);
    ck_assert_int_eq(unit.cols, result.cols);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            ck_assert_int_eq(result.element[i][j], unit.element[i][j]);

    matrix_free(&unit);
    matrix_free(&result);
}
END_TEST

START_TEST(test_matrix_mul_simple)
{
    const int frows = 4, fcols = 2;
    const int srows = 2, scols = 5;
    const int rrows = frows;
    const int rcols = scols;

    matrix_t first = { frows, fcols };
    matrix_t second = { srows, scols };
    matrix_t result;
    
    int64_t f0[] = { 1, 2 };
    int64_t f1[] = { 3, 4 };
    int64_t f2[] = { 5, 6 };
    int64_t f3[] = { 7, 8 };
    int64_t *f[] = { f0, f1, f2, f3 };
    first.element = f;

    int64_t s0[] = { 10, 20, 30, 40, 50 };
    int64_t s1[] = { 60, 70, 80, 90, 100 };
    int64_t *s[] = { s0, s1 };
    second.element = s;

    int64_t r0[] = { 130, 160, 190, 220, 250 };
    int64_t r1[] = { 270, 340, 410, 480, 550 };
    int64_t r2[] = { 410, 520, 630, 740, 850 };
    int64_t r3[] = { 550, 700, 850, 1000, 1150 };
    int64_t *r[] = { r0, r1, r2, r3 };

    exit_t exit_code = matrix_multiply(&first, &second, &result);

    ck_assert_int_eq(exit_code, 0);
    ck_assert_int_eq(rrows, result.rows);
    ck_assert_int_eq(rcols, result.cols);

    for (int i = 0; i < result.rows; i++)
        for (int j = 0; j < result.cols; j++)
            ck_assert_int_eq(r[i][j], result.element[i][j]);

    matrix_free(&result);
}
END_TEST

START_TEST(test_matrix_mul_small)
{
    const int frows = 1, fcols = 1;
    const int srows = 1, scols = 1;
    const int rrows = frows;
    const int rcols = scols;

    matrix_t first = { frows, fcols };
    matrix_t second = { srows, scols };
    matrix_t result;
    
    int64_t f0[] = { 3 };
    int64_t *f[] = { f0 };
    first.element = f;

    int64_t s0[] = { 2 };
    int64_t *s[] = { s0 };
    second.element = s;

    int64_t r0[] = { 6 };
    int64_t *r[] = { r0 };

    exit_t exit_code = matrix_multiply(&first, &second, &result);

    ck_assert_int_eq(exit_code, 0);
    ck_assert_int_eq(rrows, result.rows);
    ck_assert_int_eq(rcols, result.cols);

    for (int i = 0; i < result.rows; i++)
        for (int j = 0; j < result.cols; j++)
            ck_assert_int_eq(r[i][j], result.element[i][j]);

    matrix_free(&result);
}
END_TEST

START_TEST(test_matrix_mul_inv_sz)
{
    const int frows = 4, fcols = 3;
    const int srows = 2, scols = 5;

    matrix_t first = { frows, fcols };
    matrix_t second = { srows, scols };
    matrix_t result = { 0 };
    
    int64_t f0[] = { 1, 2, 0 };
    int64_t f1[] = { 3, 4, 0 };
    int64_t f2[] = { 5, 6, 0 };
    int64_t f3[] = { 7, 8, 0 };
    int64_t *f[] = { f0, f1, f2, f3 };
    first.element = f;

    int64_t s0[] = { 10, 20, 30, 40, 50 };
    int64_t s1[] = { 60, 70, 80, 90, 100 };
    int64_t *s[] = { s0, s1 };
    second.element = s;

    exit_t exit_code = matrix_multiply(&first, &second, &result);

    ck_assert_int_ne(exit_code, 0);

    matrix_free(&result);
}
END_TEST

START_TEST(test_matrix_mul_zero_sz)
{
    matrix_t first = { 0 };
    matrix_t second = { 0 };
    matrix_t result = { 0 };

    exit_t exit_code = matrix_multiply(&first, &second, &result);

    ck_assert_int_ne(exit_code, 0);

    matrix_free(&result);
}
END_TEST

Suite *matrix_mul_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("matrix_multiply");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_matrix_mul_unit);
    tcase_add_test(tc_pos, test_matrix_mul_simple);
    tcase_add_test(tc_pos, test_matrix_mul_small);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_matrix_mul_inv_sz);
    tcase_add_test(tc_neg, test_matrix_mul_zero_sz);
    suite_add_tcase(s, tc_neg);

    return s;
}

START_TEST(test_matrix_pw_simple_even)
{
    const int sz = 3;

    matrix_t mtx = { sz, sz };
    
    int64_t in0[] = { 1, 2, 3 };
    int64_t in1[] = { 4, 5, 6 };
    int64_t in2[] = { 7, 8, 9 };
    int64_t *in[] = { in0, in1, in2 };
    
    matrix_initialize(&mtx.element, sz, sz);

    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            mtx.element[i][j] = in[i][j];

    int64_t r0[] = { 7560, 9288, 11016 };
    int64_t r1[] = { 17118, 21033, 24948 };
    int64_t r2[] = { 26676, 32778, 38880 };
    int64_t *r[] = { r0, r1, r2 };

    exit_t exit_code = matrix_pow(&mtx, 4);

    ck_assert_int_eq(exit_code, 0);

    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            ck_assert_int_eq(r[i][j], mtx.element[i][j]);

    matrix_free(&mtx);
}
END_TEST

START_TEST(test_matrix_pw_simple_odd)
{
    const int sz = 3;

    matrix_t mtx = { sz, sz };
    
    int64_t in0[] = { 1, 2, 3 };
    int64_t in1[] = { 4, 5, 6 };
    int64_t in2[] = { 7, 8, 9 };
    int64_t *in[] = { in0, in1, in2 };
    
    matrix_initialize(&mtx.element, sz, sz);

    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            mtx.element[i][j] = in[i][j];

    int64_t r0[] = { 121824, 149688, 177552 };
    int64_t r1[] = { 275886, 338985, 402084 };
    int64_t r2[] = { 429948, 528282, 626616 };
    int64_t *r[] = { r0, r1, r2 };

    exit_t exit_code = matrix_pow(&mtx, 5);

    ck_assert_int_eq(exit_code, 0);

    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            ck_assert_int_eq(r[i][j], mtx.element[i][j]);

    matrix_free(&mtx);
}
END_TEST

START_TEST(test_matrix_pw_simple_zero)
{
    const int sz = 3;

    matrix_t mtx = { sz, sz };
    
    int64_t in0[] = { 1, 2, 3 };
    int64_t in1[] = { 4, 5, 6 };
    int64_t in2[] = { 7, 8, 9 };
    int64_t *in[] = { in0, in1, in2 };
    
    matrix_initialize(&mtx.element, sz, sz);

    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            mtx.element[i][j] = in[i][j];

    int64_t r0[] = { 1, 0, 0 };
    int64_t r1[] = { 0, 1, 0 };
    int64_t r2[] = { 0, 0, 1 };
    int64_t *r[] = { r0, r1, r2 };

    exit_t exit_code = matrix_pow(&mtx, 0);

    ck_assert_int_eq(exit_code, 0);

    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            ck_assert_int_eq(r[i][j], mtx.element[i][j]);

    matrix_free(&mtx);
}
END_TEST

START_TEST(test_matrix_pw_simple_one)
{
    const int sz = 3;

    matrix_t mtx = { sz, sz };
    
    int64_t in0[] = { 1, 2, 3 };
    int64_t in1[] = { 4, 5, 6 };
    int64_t in2[] = { 7, 8, 9 };
    int64_t *in[] = { in0, in1, in2 };
    
    matrix_initialize(&mtx.element, sz, sz);

    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            mtx.element[i][j] = in[i][j];

    int64_t r0[] = { 1, 2, 3 };
    int64_t r1[] = { 4, 5, 6 };
    int64_t r2[] = { 7, 8, 9 };
    int64_t *r[] = { r0, r1, r2 };

    exit_t exit_code = matrix_pow(&mtx, 1);

    ck_assert_int_eq(exit_code, 0);

    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            ck_assert_int_eq(r[i][j], mtx.element[i][j]);

    matrix_free(&mtx);
}
END_TEST

START_TEST(test_matrix_pw_not_a_square)
{
    matrix_t mtx = { 2, 3 };
    
    int64_t in0[] = { 1, 2 };
    int64_t in1[] = { 4, 5 };
    int64_t in2[] = { 7, 8 };
    int64_t *in[] = { in0, in1, in2 };
    
    matrix_initialize(&mtx.element, 2, 3);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            mtx.element[i][j] = in[i][j];

    exit_t exit_code = matrix_pow(&mtx, 1);

    ck_assert_int_ne(exit_code, 0);

    matrix_free(&mtx);
}
END_TEST

Suite *matrix_pow_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("matrix_power");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_matrix_pw_simple_even);
    tcase_add_test(tc_pos, test_matrix_pw_simple_odd);
    tcase_add_test(tc_pos, test_matrix_pw_simple_zero);
    tcase_add_test(tc_pos, test_matrix_pw_simple_one);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_matrix_pw_not_a_square);
    suite_add_tcase(s, tc_neg);

    return s;
}

START_TEST(test_to_square_square)
{
    const int rows = 3, cols = 3;
    int64_t in0[] = { 0, 1, 2 };
    int64_t in1[] = { 3, 4, 5 };
    int64_t in2[] = { 6, 7, 8 };
    int64_t *in[] = { in0, in1, in2 };

    matrix_t mtx = { 0 };
    matrix_initialize(&mtx.element, rows, cols);
    mtx.rows = rows;
    mtx.cols = cols;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            mtx.element[i][j] = in[i][j];

    exit_t exit_code = matrix_to_square(&mtx);

    ck_assert_int_eq(exit_code, 0);

    ck_assert_int_eq(mtx.rows, min(rows, cols));
    ck_assert_int_eq(mtx.cols, min(rows, cols));

    for (int i = 0; i < mtx.rows; i++)
        for (int j = 0; j < mtx.cols; j++)
            ck_assert_int_eq(mtx.element[i][j], in[i][j]);

    matrix_free(&mtx);
}
END_TEST

START_TEST(test_to_square_column)
{
    const int rows = 5, cols = 1;
    int64_t in0[] = { 0 };
    int64_t in1[] = { 1 };
    int64_t in2[] = { 2 };
    int64_t in3[] = { 3 };
    int64_t in4[] = { 4 };
    int64_t *in[] = { in0, in1, in2, in3, in4 };

    int64_t res0[] = { 0 };
    int64_t *res[] = { res0 };

    matrix_t mtx;
    matrix_initialize(&mtx.element, rows, cols);
    mtx.rows = rows;
    mtx.cols = cols;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            mtx.element[i][j] = in[i][j];

    exit_t exit_code = matrix_to_square(&mtx);

    ck_assert_int_eq(exit_code, 0);
    ck_assert_int_eq(mtx.rows, min(rows, cols));
    ck_assert_int_eq(mtx.cols, min(rows, cols));

    for (int i = 0; i < mtx.rows; i++)
        for (int j = 0; j < mtx.cols; j++)
            ck_assert_int_eq(mtx.element[i][j], res[i][j]);

    matrix_free(&mtx);
}
END_TEST

START_TEST(test_to_square_row)
{
    const int rows = 1, cols = 5;
    int64_t in0[] = { 0, 1, 2, 3, 4, 5 };
    int64_t *in[] = { in0 };

    int64_t res0[] = { 0 };
    int64_t *res[] = { res0 };

    matrix_t mtx;
    matrix_initialize(&mtx.element, rows, cols);
    mtx.rows = rows;
    mtx.cols = cols;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            mtx.element[i][j] = in[i][j];

    exit_t exit_code = matrix_to_square(&mtx);

    ck_assert_int_eq(exit_code, 0);
    ck_assert_int_eq(mtx.rows, min(rows, cols));
    ck_assert_int_eq(mtx.cols, min(rows, cols));

    for (int i = 0; i < mtx.rows; i++)
        for (int j = 0; j < mtx.cols; j++)
            ck_assert_int_eq(mtx.element[i][j], res[i][j]);

    matrix_free(&mtx);
}
END_TEST

START_TEST(test_to_square_eq_els_row)
{
    const int rows = 5, cols = 3;
    int64_t in0[] = { 0, 2, 3 };
    int64_t in1[] = { 10, 0, 4 };
    int64_t in2[] = { 2, -1, 7 };
    int64_t in3[] = { 3, 10, 4 };
    int64_t in4[] = { 4, 5, 10 };
    int64_t *in[] = { in0, in1, in2, in3, in4 };

    int64_t res0[] = { 0, 2, 3 };
    int64_t res1[] = { 10, 0, 4 };
    int64_t res2[] = { 2, -1, 7 };
    int64_t *res[] = { res0, res1, res2 };

    matrix_t mtx;
    matrix_initialize(&mtx.element, rows, cols);
    mtx.rows = rows;
    mtx.cols = cols;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            mtx.element[i][j] = in[i][j];

    exit_t exit_code = matrix_to_square(&mtx);

    ck_assert_int_eq(exit_code, 0);
    ck_assert_int_eq(mtx.rows, min(rows, cols));
    ck_assert_int_eq(mtx.cols, min(rows, cols));

    for (int i = 0; i < mtx.rows; i++)
        for (int j = 0; j < mtx.cols; j++)
            ck_assert_int_eq(mtx.element[i][j], res[i][j]);

    matrix_free(&mtx);
}
END_TEST

START_TEST(test_to_square_eq_els_col)
{
    const int rows = 3, cols = 5;
    int64_t in0[] = { 0, 2, 10, 3, 5 };
    int64_t in1[] = { 10, 0, 4, 4, 9 };
    int64_t in2[] = { 2, -1, 7, 7, 10 };
    int64_t *in[] = { in0, in1, in2 };

    int64_t res0[] = { 0, 2, 3 };
    int64_t res1[] = { 10, 0, 4 };
    int64_t res2[] = { 2, -1, 7 };
    int64_t *res[] = { res0, res1, res2 };

    matrix_t mtx;
    matrix_initialize(&mtx.element, rows, cols);
    mtx.rows = rows;
    mtx.cols = cols;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            mtx.element[i][j] = in[i][j];

    exit_t exit_code = matrix_to_square(&mtx);

    ck_assert_int_eq(exit_code, 0);
    ck_assert_int_eq(mtx.rows, min(rows, cols));
    ck_assert_int_eq(mtx.cols, min(rows, cols));

    for (int i = 0; i < mtx.rows; i++)
        for (int j = 0; j < mtx.cols; j++)
            ck_assert_int_eq(mtx.element[i][j], res[i][j]);

    matrix_free(&mtx);
}
END_TEST

START_TEST(test_to_square_null)
{
    matrix_t mtx = { 0 };

    exit_t exit_code = matrix_to_square(&mtx);

    ck_assert_int_ne(exit_code, 0);
}
END_TEST

Suite *matrix_to_square_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("matrix_to_square");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_to_square_square);
    tcase_add_test(tc_pos, test_to_square_column);
    tcase_add_test(tc_pos, test_to_square_row);
    tcase_add_test(tc_pos, test_to_square_eq_els_row);
    tcase_add_test(tc_pos, test_to_square_eq_els_col);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_to_square_null);
    suite_add_tcase(s, tc_neg);

    return s;
}

START_TEST(test_to_eq_sz_squares)
{
    matrix_t first = { 3, 3 };
    matrix_t second = { 2, 2 };
    
    int64_t f0[] = { 1, 2, 3 };
    int64_t f1[] = { 4, 5, 6 };
    int64_t f2[] = { 7, 8, 9 };
    int64_t *f[] = { f0, f1, f2 };

    int64_t s0[] = { 1, 2 };
    int64_t s1[] = { 4, 5 };
    int64_t *s[] = { s0, s1 };

    int64_t se0[] = { 1, 2, 1 };
    int64_t se1[] = { 4, 5, 4 };
    int64_t se2[] = { 2, 3, 2 };
    int64_t *se[] = { se0, se1, se2 };
    
    matrix_initialize(&first.element, first.rows, first.cols);
    for (int i = 0; i < first.rows; i++)
        for (int j = 0; j < first.cols; j++)
            first.element[i][j] = f[i][j];
    
    matrix_initialize(&second.element, second.rows, second.cols);
    for (int i = 0; i < second.rows; i++)
        for (int j = 0; j < second.cols; j++)
            second.element[i][j] = s[i][j];

    exit_t exit_code = matrix_to_same_size(&first, &second);

    ck_assert_int_eq(exit_code, 0);
    
    ck_assert_int_eq(first.rows, 3);
    ck_assert_int_eq(first.cols, 3);

    ck_assert_int_eq(second.rows, 3);
    ck_assert_int_eq(second.cols, 3);

    for (int i = 0; i < first.rows; i++)
        for (int j = 0; j < first.cols; j++)
            ck_assert_int_eq(first.element[i][j], f[i][j]);

    for (int i = 0; i < first.rows; i++)
        for (int j = 0; j < first.cols; j++)
            ck_assert_int_eq(second.element[i][j], se[i][j]);

    matrix_free(&first);
    matrix_free(&second);
}
END_TEST

START_TEST(test_to_eq_sz_simple)
{
    matrix_t first = { 3, 2 };
    matrix_t second = { 2, 3 };
    
    int64_t f0[] = { 1, 2 };
    int64_t f1[] = { 4, 5 };
    int64_t f2[] = { 1, 20 };
    int64_t *f[] = { f0, f1, f2 };

    int64_t s0[] = { 1, 2, 9 };
    int64_t s1[] = { 4, 5, 19 };
    int64_t *s[] = { s0, s1 };

    int64_t fe0[] = { 1, 2, 1 };
    int64_t fe1[] = { 4, 5, 4 };
    int64_t fe2[] = { 1, 20, 1 };
    int64_t *fe[] = { fe0, fe1, fe2 };

    int64_t se0[] = { 1, 2, 9 };
    int64_t se1[] = { 4, 5, 19 };
    int64_t se2[] = { 2, 3, 14 };
    int64_t *se[] = { se0, se1, se2 };
    
    matrix_initialize(&first.element, first.rows, first.cols);
    for (int i = 0; i < first.rows; i++)
        for (int j = 0; j < first.cols; j++)
            first.element[i][j] = f[i][j];
    
    matrix_initialize(&second.element, second.rows, second.cols);
    for (int i = 0; i < second.rows; i++)
        for (int j = 0; j < second.cols; j++)
            second.element[i][j] = s[i][j];

    exit_t exit_code = matrix_to_same_size(&first, &second);

    ck_assert_int_eq(exit_code, 0);
    
    ck_assert_int_eq(first.rows, 3);
    ck_assert_int_eq(first.cols, 3);

    ck_assert_int_eq(second.rows, 3);
    ck_assert_int_eq(second.cols, 3);

    for (int i = 0; i < first.rows; i++)
        for (int j = 0; j < first.cols; j++)
            ck_assert_int_eq(first.element[i][j], fe[i][j]);

    for (int i = 0; i < first.rows; i++)
        for (int j = 0; j < first.cols; j++)
            ck_assert_int_eq(second.element[i][j], se[i][j]);

    matrix_free(&first);
    matrix_free(&second);
}
END_TEST

START_TEST(test_to_eq_sz_rowcol)
{
    matrix_t first = { 3, 1 };
    matrix_t second = { 1, 3 };
    
    int64_t f0[] = { 1 };
    int64_t f1[] = { 4 };
    int64_t f2[] = { -1 };
    int64_t *f[] = { f0, f1, f2 };

    int64_t s0[] = { 1, -2, 9 };
    int64_t *s[] = { s0 };

    int64_t fe0[] = { 1, 1, 1 };
    int64_t fe1[] = { 4, 4, 4 };
    int64_t fe2[] = { -1, -1, -1 };
    int64_t *fe[] = { fe0, fe1, fe2 };

    int64_t se0[] = { 1, -2, 9 };
    int64_t se1[] = { 1, -2, 9 };
    int64_t se2[] = { 1, -2, 9 };
    int64_t *se[] = { se0, se1, se2 };
    
    matrix_initialize(&first.element, first.rows, first.cols);
    for (int i = 0; i < first.rows; i++)
        for (int j = 0; j < first.cols; j++)
            first.element[i][j] = f[i][j];
    
    matrix_initialize(&second.element, second.rows, second.cols);
    for (int i = 0; i < second.rows; i++)
        for (int j = 0; j < second.cols; j++)
            second.element[i][j] = s[i][j];

    exit_t exit_code = matrix_to_same_size(&first, &second);

    ck_assert_int_eq(exit_code, 0);
    
    ck_assert_int_eq(first.rows, 3);
    ck_assert_int_eq(first.cols, 3);

    ck_assert_int_eq(second.rows, 3);
    ck_assert_int_eq(second.cols, 3);

    for (int i = 0; i < first.rows; i++)
        for (int j = 0; j < first.cols; j++)
            ck_assert_int_eq(first.element[i][j], fe[i][j]);

    for (int i = 0; i < first.rows; i++)
        for (int j = 0; j < first.cols; j++)
            ck_assert_int_eq(second.element[i][j], se[i][j]);

    matrix_free(&first);
    matrix_free(&second);
}
END_TEST

Suite *matrix_to_eq_sz_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("matrix_to_eq_sz");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_to_eq_sz_squares);
    tcase_add_test(tc_pos, test_to_eq_sz_simple);
    tcase_add_test(tc_pos, test_to_eq_sz_rowcol);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    suite_add_tcase(s, tc_neg);

    return s;
}

int main(void)
{
    int failed = 0;
    Suite *s = matrix_mul_suite();

    SRunner *runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    s = matrix_pow_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    s = matrix_to_square_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    s = matrix_to_eq_sz_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return failed;
}