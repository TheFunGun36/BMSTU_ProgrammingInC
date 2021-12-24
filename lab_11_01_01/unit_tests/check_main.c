#include "mylib.h"
#include <check.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 256

START_TEST(test_dec)
{
    char str_expected[BUFFER_SIZE];
    char str[BUFFER_SIZE];
    int ret_expected = snprintf(str_expected, 18, "%d, %d, %d, %d\n", 123, 456, 0, -10);
    int ret = my_snprintf(str, 18, "%d, %d, %d, %d\n", 123, 456, 0, -10);

    ck_assert_int_eq(ret_expected, ret);
    ck_assert_int_eq(strcmp(str_expected, str), 0);
}
END_TEST

START_TEST(test_dec_cut)
{
    char str_expected[BUFFER_SIZE];
    char str[BUFFER_SIZE];
    int ret_expected = snprintf(str_expected, 8, "%d, %d, %d, %d\n", 123, 456, 0, -10);;
    int ret = my_snprintf(str, 8, "%d, %d, %d, %d\n", 123, 456, 0, -10);

    ck_assert_int_eq(ret_expected, ret);
    ck_assert_int_eq(strcmp(str_expected, str), 0);
}
END_TEST

START_TEST(test_dec_cut_neg)
{
    char str_expected[BUFFER_SIZE];
    char str[BUFFER_SIZE];
    int ret_expected = snprintf(str_expected, 17, "%d, %d, %d, %d\n", 123, 456, 0, -123);
    int ret = my_snprintf(str, 17, "%d, %d, %d, %d\n", 123, 456, 0, -123);

    ck_assert_int_eq(ret_expected, ret);
    ck_assert_int_eq(strcmp(str_expected, str), 0);
}
END_TEST

START_TEST(test_dec_cut_neg_minus)
{
    char str_expected[BUFFER_SIZE];
    char str[BUFFER_SIZE];
    int ret_expected = snprintf(str_expected, 15, "%d, %d, %d, %d\n", 123, 456, 0, -123);
    int ret = my_snprintf(str, 15, "%d, %d, %d, %d\n", 123, 456, 0, -123);

    ck_assert_int_eq(ret_expected, ret);
    ck_assert_int_eq(strcmp(str_expected, str), 0);
}
END_TEST

START_TEST(test_oct)
{
    char str_expected[BUFFER_SIZE];
    char str[BUFFER_SIZE];
    int ret_expected = snprintf(str_expected, 15, "%o, %o, %o\n", 511, 106, 0);
    int ret = my_snprintf(str, 15, "%o, %o, %o\n", 511, 106, 0);

    ck_assert_int_eq(ret_expected, ret);
    ck_assert_int_eq(strcmp(str_expected, str), 0);
}
END_TEST

START_TEST(test_oct_cut)
{
    char str_expected[BUFFER_SIZE];
    char str[BUFFER_SIZE];
    int ret_expected = snprintf(str_expected, 8, "%o, %o, %o\n", 511, 106, 0);
    int ret = my_snprintf(str, 8, "%o, %o, %o\n", 511, 106, 0);

    ck_assert_int_eq(ret_expected, ret);
    ck_assert_int_eq(strcmp(str_expected, str), 0);
}
END_TEST

START_TEST(test_str)
{
    char str_expected[BUFFER_SIZE];
    char str[BUFFER_SIZE];
    char str1[] = "aboba";
    char str2[] = "klass";

    int ret_expected = snprintf(str_expected, 25, "%s, bobiba, %s", str1, str2);
    int ret = my_snprintf(str, 25, "%s, bobiba, %s", str1, str2);

    ck_assert_int_eq(ret_expected, ret);
    ck_assert_int_eq(strcmp(str_expected, str), 0);
}
END_TEST

START_TEST(test_str_cut)
{
    char str_expected[BUFFER_SIZE];
    char str1[] = "aboba";
    char str2[] = "klass";

    char str[BUFFER_SIZE];
    int ret_expected = snprintf(str_expected, 18, "%s, bobiba, %s", str1, str2);
    int ret = my_snprintf(str, 18, "%s, bobiba, %s", str1, str2);

    ck_assert_int_eq(ret_expected, ret);
    ck_assert_int_eq(strcmp(str_expected, str), 0);
}
END_TEST

START_TEST(test_chr)
{
    char str_expected[BUFFER_SIZE];
    char str[BUFFER_SIZE];

    int ret_expected = snprintf(str_expected, 26, "hello, %c %c %c %c %c (%c%c%c%c%c)\n", 'A', 'B', 'O', 'B', 'A', 'a', 'b', 'o', 'b', 'a');
    int ret = my_snprintf(str, 26, "hello, %c %c %c %c %c (%c%c%c%c%c)\n", 'A', 'B', 'O', 'B', 'A', 'a', 'b', 'o', 'b', 'a');

    ck_assert_int_eq(ret_expected, ret);
    ck_assert_int_eq(strcmp(str_expected, str), 0);
}
END_TEST

Suite *goods_filter_suite(void)
{
    Suite *s = suite_create("my_snprintf");

    TCase *tdc = tcase_create("decimal");
    tcase_add_test(tdc, test_dec);
    tcase_add_test(tdc, test_dec_cut);
    tcase_add_test(tdc, test_dec_cut_neg);
    tcase_add_test(tdc, test_dec_cut_neg_minus);
    suite_add_tcase(s, tdc);

    TCase *toc = tcase_create("octonal");
    tcase_add_test(toc, test_oct);
    tcase_add_test(toc, test_oct_cut);
    suite_add_tcase(s, toc);

    TCase *tsc = tcase_create("string");
    tcase_add_test(tsc, test_str);
    tcase_add_test(tsc, test_str_cut);
    suite_add_tcase(s, tsc);

    TCase *tcc = tcase_create("chars");
    tcase_add_test(tcc, test_chr);
    suite_add_tcase(s, tcc);

    return s;
}

int main(void)
{
    int failed = 0;

    Suite *s = goods_filter_suite();
    SRunner *runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return failed;
}
