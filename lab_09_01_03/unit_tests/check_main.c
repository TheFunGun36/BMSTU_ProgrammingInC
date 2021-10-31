#include <check.h>
#include <string.h>
#include <stdlib.h>
#include "goods.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))

static int comp(product_t prod, product_t sample)
{
    return prod.price < sample.price;
}

START_TEST(goods_filter_test_simple)
{
    goods_t goods;
    goods.amount = 5;
    goods.val = malloc(goods.amount * sizeof(product_t));

    {
        product_t tmp[] = {
            { 3, NULL },
            { 9, NULL },
            { 5, NULL },
            { 6, NULL },
            { 1, NULL }
        };

        memcpy(goods.val, tmp, sizeof(tmp));
    }

    product_t sample = { 6, NULL };

    goods_filter(&goods, sample, comp);

    ck_assert_int_eq(goods.amount, 3);

    ck_assert_int_eq(goods.val[0].price, 3);
    ck_assert_int_eq(goods.val[1].price, 5);
    ck_assert_int_eq(goods.val[2].price, 1);

    free(goods.val);
}
END_TEST

Suite *goods_filter_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("goods_filter_suite");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, goods_filter_test_simple);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    suite_add_tcase(s, tc_neg);

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