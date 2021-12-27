#include <check.h>
#include <stdlib.h>
#include "product.h"

int is_parr_eq(product_t *a, product_t *b, int size)
{
    int res = 1;

    for (int i = 0; i < size && res; i++)
    {
        res = !strcmp(a->name, b->name);
        res &= a->price == b->price;
    }

    return res;
}

START_TEST(test_filter1)
{
    char *s1 = malloc(4 * sizeof(char));
    strcpy(s1, "jkh");

    product_t in[] = {
        { .name="abc", .price=1 },
        { .name="112", .price=5 },
        { .name=s1, .price=10U },
        { .name="goga", .price=6U }
    };

    product_t out[] = {
        { .name="abc", .price=1 },
        { .name="112", .price=5 },
        { .name="goga", .price=6U }
    };

    unsigned int size = sizeof(in) / sizeof(product_t);

    filter_product_array(in, &size, 6.5);
    ck_assert_uint_eq(size, sizeof(out) / sizeof(product_t));
    ck_assert_uint_eq(is_parr_eq(in, out, size), 1);
}
END_TEST

START_TEST(test_filter2)
{
    char *s1 = malloc(4 * sizeof(char));
    strcpy(s1, "jkh");
    
    char *s2 = malloc(5 * sizeof(char));
    strcpy(s2, "goga");

    product_t in[] = {
        { "112", 5 },
        { "abc", 1 },
        { s1, 10 },
        { s2, 6 }
    };

    product_t out[] = {
        { "112", 5 },
        { "abc", 1 }
    };

    unsigned int size = sizeof(in) / sizeof(product_t);

    filter_product_array(in, &size, 6.0);
    ck_assert_int_eq(size, sizeof(out) / sizeof(product_t));
    ck_assert_int_eq(is_parr_eq(in, out, size), 1);
}
END_TEST

START_TEST(test_filter3)
{
    char *s1 = malloc(4 * sizeof(char));
    strcpy(s1, "jkh");
    
    char *s2 = malloc(5 * sizeof(char));
    strcpy(s2, "goga");

    char *s3 = malloc(4 * sizeof(char));
    strcpy(s1, "112");

    product_t in[] = {
        { s3, 5 },
        { "abc", 1 },
        { s1, 10 },
        { s2, 6 }
    };

    product_t out[] = {
        { "abc", 1 }
    };

    unsigned int size = sizeof(in) / sizeof(product_t);

    filter_product_array(in, &size, 2);
    ck_assert_int_eq(size, sizeof(out) / sizeof(product_t));
    ck_assert_int_eq(is_parr_eq(in, out, size), 1);
}
END_TEST

Suite *main_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("filter_product_array");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_filter1);
    tcase_add_test(tc_pos, test_filter2);
    tcase_add_test(tc_pos, test_filter3);
    suite_add_tcase(s, tc_pos);

    return s;
}

int main(void)
{
    int failed = 0;
    Suite *s = main_suite();

    SRunner *runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return failed;
}
