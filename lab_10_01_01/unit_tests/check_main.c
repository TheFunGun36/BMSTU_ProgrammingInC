#include <check.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define BUFFER_SIZE 256

int int_comp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

START_TEST(test_insert_front)
{
    int values[] = { 0, 1, 2, 3, 4 };

    node_t *list = NULL;

    for (int i = 0; i < sizeof(values)/sizeof(int); i++)
    {
        node_t *node = malloc(sizeof(node_t));
        node->data = values + i;
        insert(&list, node, list);
    }

    node_t *node = list;
    for (int i = 0; i < sizeof(values)/sizeof(int); i++)
    {
        ck_assert_int_eq(*(int*)node->data, values[sizeof(values)/sizeof(int) - i - 1]);
        node = node->next;
    }
    ck_assert_ptr_eq(node, NULL);

    clear(&list);
}
END_TEST

START_TEST(test_insert_back)
{
    int values[] = { 0, 1, 2, 3, 4 };

    node_t *list = NULL;

    for (int i = 0; i < sizeof(values)/sizeof(int); i++)
    {
        node_t *node = malloc(sizeof(node_t));
        node->data = values + i;
        insert(&list, node, NULL);
    }

    node_t *node = list;
    for (int i = 0; i < sizeof(values)/sizeof(int); i++)
    {
        ck_assert_int_eq(*(int*)node->data, values[i]);
        node = node->next;
    }
    ck_assert_ptr_eq(node, NULL);

    clear(&list);
}
END_TEST

START_TEST(test_insert_mid)
{
    int values[] = { 0, 1, 2, 3, 4, 5, 6 };
    int expected[] = { 0, 1, 2, 6, 3, 4, 5 };

    node_t *list = NULL;

    for (int i = 0; i < sizeof(values)/sizeof(int); i++)
    {
        node_t *node = malloc(sizeof(node_t));
        node->data = values + i;
        if (i == sizeof(values)/sizeof(int) - 1)
            insert(&list, node, list->next->next->next);
        else
            insert(&list, node, NULL);
    }

    node_t *node = list;
    for (int i = 0; i < sizeof(values)/sizeof(int); i++)
    {
        ck_assert_int_eq(*(int*)node->data, expected[i]);

        node = node->next;
    }
    ck_assert_ptr_eq(node, NULL);

    clear(&list);
}
END_TEST

START_TEST(test_pop_back)
{
    int values[] = { 0, 1, 2, 3, 4 };

    node_t *list = NULL;

    for (int i = 0; i < sizeof(values)/sizeof(int); i++)
    {
        node_t *node = malloc(sizeof(node_t));
        node->data = values + i;
        insert(&list, node, NULL);
    }

    ck_assert_ptr_eq(pop_back(&list), values + 4);

    node_t *node = list;
    for (int i = 0; i < sizeof(values)/sizeof(int) - 1; i++)
    {
        ck_assert_int_eq(*(int*)node->data, values[i]);
        node = node->next;
    }
    ck_assert_ptr_eq(node, NULL);

    clear(&list);
}
END_TEST

START_TEST(test_pop_front)
{
    int values[] = { 0, 1, 2, 3, 4 };

    node_t *list = NULL;

    for (int i = 0; i < sizeof(values)/sizeof(int); i++)
    {
        node_t *node = malloc(sizeof(node_t));
        node->data = values + i;
        insert(&list, node, NULL);
    }

    ck_assert_int_eq(*(int*)pop_front(&list), values[0]);

    node_t *node = list;
    for (int i = 0; i < sizeof(values)/sizeof(int) - 1; i++)
    {
        ck_assert_int_eq(*(int*)node->data, values[i + 1]);
        node = node->next;
    }
    ck_assert_ptr_eq(node, NULL);

    clear(&list);
}
END_TEST

START_TEST(test_find)
{
    int values[] = { 0, 1, 2, 3, 4 };
    int spec_val = -1;
    node_t *list = NULL;

    for (int i = 0; i < sizeof(values)/sizeof(int); i++)
    {
        node_t *node = malloc(sizeof(node_t));
        node->data = values + i;
        insert(&list, node, NULL);
    }

    ck_assert_int_eq(*(int*)find(list, values + 0, int_comp)->data, values[0]);
    ck_assert_int_eq(*(int*)find(list, values + 3, int_comp)->data, values[3]);
    ck_assert_int_eq(*(int*)find(list, values + 4, int_comp)->data, values[4]);
    ck_assert_ptr_eq(find(list, &spec_val, int_comp), NULL);

    node_t *node = list;
    for (int i = 0; i < sizeof(values)/sizeof(int); i++)
    {
        ck_assert_int_eq(*(int*)node->data, values[i]);
        node = node->next;
    }
    ck_assert_ptr_eq(node, NULL);

    clear(&list);
}
END_TEST

START_TEST(test_remove_duplicates)
{
    int values[] = { 7, 8, 1, 3, 2, 2, 7, 4, 1, 4, 5, 9, 8, 6, 5, 5, 5, 0, 3, 6, 0, };
    int expected[] = { 7, 8, 1, 3, 2, 4, 5, 9, 6, 0 };
    node_t *list = NULL;

    for (int i = 0; i < sizeof(values) / sizeof(int); i++)
    {
        node_t *node = malloc(sizeof(node_t));
        node->data = values + i;
        insert(&list, node, NULL);
    }

    remove_duplicates(&list, int_comp);

    node_t *node = list;
    for (int i = 0; i < sizeof(expected) / sizeof(int); i++)
    {
        ck_assert_int_eq(*(int*)node->data, expected[i]);
        node = node->next;
    }
    ck_assert_ptr_eq(node, NULL);

    clear(&list);
}
END_TEST

START_TEST(test_sort)
{
    int values[] = { 7, 8, 1, 3, 2, 4, 5, 9, 6, 0 };
    node_t *list = NULL;

    for (int i = 0; i < sizeof(values) / sizeof(int); i++)
    {
        node_t *node = malloc(sizeof(node_t));
        node->data = values + i;
        insert(&list, node, NULL);
    }

    sort(&list, int_comp);

    node_t *node = list;
    for (int i = 0; i < sizeof(values) / sizeof(int); i++)
    {
        ck_assert_int_eq(*(int*)node->data, i);
        node = node->next;
    }
    ck_assert_ptr_eq(node, NULL);

    clear(&list);
}
END_TEST

START_TEST(test_sort_odd)
{
    int values[] = { 7, 8, 1, 3, 2, 4, 5, 9, 6, 0, 10 };
    node_t *list = NULL;

    for (int i = 0; i < sizeof(values) / sizeof(int); i++)
    {
        node_t *node = malloc(sizeof(node_t));
        node->data = values + i;
        insert(&list, node, NULL);
    }

    sort(&list, int_comp);

    node_t *node = list;
    for (int i = 0; i < sizeof(values) / sizeof(int); i++)
    {
        ck_assert_int_eq(*(int*)node->data, i);
        node = node->next;
    }
    ck_assert_ptr_eq(node, NULL);

    clear(&list);
}
END_TEST

START_TEST(test_sort_single)
{
    int values[] = { 0 };
    node_t *list = NULL;

    for (int i = 0; i < sizeof(values) / sizeof(int); i++)
    {
        node_t *node = malloc(sizeof(node_t));
        node->data = values + i;
        insert(&list, node, NULL);
    }

    sort(&list, int_comp);

    node_t *node = list;
    for (int i = 0; i < sizeof(values) / sizeof(int); i++)
    {
        ck_assert_int_eq(*(int*)node->data, i);
        node = node->next;
    }
    ck_assert_ptr_eq(node, NULL);

    clear(&list);
}
END_TEST

Suite *main_suite(void)
{
    Suite *s = suite_create("list");

    TCase *tc1 = tcase_create("single_element_task");
    tcase_add_test(tc1, test_insert_front);
    tcase_add_test(tc1, test_insert_back);
    tcase_add_test(tc1, test_insert_mid);
    tcase_add_test(tc1, test_pop_back);
    tcase_add_test(tc1, test_pop_front);
    tcase_add_test(tc1, test_find);
    suite_add_tcase(s, tc1);

    TCase *tc2 = tcase_create("multi_element_task");
    tcase_add_test(tc2, test_remove_duplicates);
    tcase_add_test(tc2, test_sort);
    tcase_add_test(tc2, test_sort_odd);
    tcase_add_test(tc2, test_sort_single);
    suite_add_tcase(s, tc2);

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
