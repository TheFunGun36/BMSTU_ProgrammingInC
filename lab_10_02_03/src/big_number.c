#include "big_number.h"
#include "dynamic_array.h"
#include <stdio.h>

static int add_prime(int_darr_t *arr)
{
    int exit_code = ARR_OK;

    if (!arr)
    {
        exit_code = ARR_INVALID_PTR;
    }
    else
    {
        if (!arr->data)
        {
            exit_code = int_darr_add(arr, 2);
        }
        else
        {
            int is_prime = 0;
            int prime;
            for (prime = arr->data[arr->size - 1] + 1; !is_prime; prime++)
            {
                is_prime = 1;
                for (int i = 0; is_prime && arr->data[i] * arr->data[i] <= prime; i++)
                    is_prime = prime % arr->data[i];
            }

            prime--;
            exit_code = int_darr_add(arr, prime);
        }
    }

    return exit_code;
}

node_t *bign_from_int(int value, int_darr_t *primes_arr, int *exit_code)
{
    node_t *result = NULL;
    node_t *tail = result;

    if (primes_arr && value > 0)
    {
        *exit_code = ARR_OK;

        for (int i = 0; *exit_code == ARR_OK && value > 1; i++)
        {
            if (primes_arr->size <= i)
                *exit_code = add_prime(primes_arr);

            if (*exit_code == ARR_OK)
            {
                node_t *elem = malloc(sizeof(node_t));

                if (elem)
                    result = push_back(result, &tail, elem);
                else
                    *exit_code = ARR_NO_MEMORY;
            }

            if (*exit_code == ARR_OK)
            {
                int *val = calloc(1, sizeof(int));

                if (val)
                    tail->data = val;
                else
                    *exit_code = ARR_NO_MEMORY;
            }

            if (*exit_code == ARR_OK)
            {
                while (value % primes_arr->data[i] == 0)
                {
                    value /= primes_arr->data[i];
                    (*(int*)tail->data)++;
                }
            }
        }

        if (*exit_code != ARR_OK)
            clear(&result, 1);
    }

    return result;
}

node_t *bign_multiply(node_t **a, node_t **b)
{
    node_t *result = NULL;

    if (a && b)
    {
        if (list_length(*a) < list_length(*b))
        {
            node_t **tmp = a;
            a = b;
            b = tmp;
        }

        node_t *cur_a = *a;
        node_t *cur_b = *b;

        while (cur_b)
        {
            *(int*)cur_a->data += *(int*)cur_b->data;

            cur_a = cur_a->next;
            cur_b = cur_b->next;
        }

        if (*b != *a)
            clear(b, 1);

        result = *a;
        *a = NULL;
    }

    return result;
}

void bign_square(node_t *number)
{
    node_t *cur = number;

    while (cur)
    {
        *(int*)cur->data <<= 1;
        cur = cur->next;
    }
}

void bign_print(node_t *number)
{
    while (number)
    {
        printf("%d ", *(int*)number->data);
        number = number->next;
    }

    printf("L\n");
}

node_t *bign_divide(node_t **a, node_t **b, int *found_negatives)
{
    *found_negatives = 0;
    node_t *result = NULL;

    if (a && b && *a)
    {
        if (list_length(*a) >= list_length(*b))
        {
            node_t *cur_a = *a;
            node_t *cur_b = *b;
            node_t *last_non_zero = cur_a;

            while (cur_b)
            {
                *(int*)cur_a->data -= *(int*)cur_b->data;

                *found_negatives |= *(int*)cur_a->data < 0;

                if (*(int*)cur_a->data != 0)
                    last_non_zero = cur_a;

                cur_a = cur_a->next;
                cur_b = cur_b->next;
            }

            while (cur_a)
            {
                if (*(int*)cur_a->data != 0)
                    last_non_zero = cur_a;

                cur_a = cur_a->next;
            }

            if (*b != *a)
                clear(b, 1);

            while(last_non_zero->next && *(int*)last_non_zero->next->data)
                last_non_zero = last_non_zero->next;

            if (*(int*)last_non_zero->data)
                clear(&last_non_zero->next, 1);
            else
                clear(a, 1);

            result = *a;
            *a = NULL;
        }
        else
        {
            clear(a, 1);
            clear(b, 1);
        }
    }

    return result;
}
