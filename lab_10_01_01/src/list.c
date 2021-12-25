#include "list.h"
#include <stdlib.h>

void remove_element(node_t **head, node_t *after);
void front_back_split(node_t *head, node_t **back);
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *));

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *))
{
    node_t *result = NULL;

    if (comparator)
    {
        while (head && !result)
        {
            if (!comparator(head->data, data))
                result = head;
            else
                head = head->next;
        }
    }

    return result;
}

void *pop_front(node_t **head)
{
    void *result = NULL;

    if (head && *head)
    {
        result = (*head)->data;
        node_t *head_old = *head;
        *head = head_old->next;
        free(head_old);
    }

    return result;
}

void *pop_back(node_t **head)
{
    void *result = NULL;

    if (head && *head)
    {
        if ((*head)->next)
        {
            node_t *pre_tail = *head;

            while (pre_tail->next->next)
                pre_tail = pre_tail->next;

            result = pre_tail->next->data;
            free(pre_tail->next);
            pre_tail->next = NULL;
        }
        else
        {
            result = (*head)->data;
            free(*head);
            *head = NULL;
        }
    }

    return result;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    if (head && elem)
    {
        elem->next = before;

        if (*head)
        {
            if (before != *head)
            {
                node_t *after = *head;

                while (after->next != NULL && after->next != before)
                    after = after->next;

                if (after->next != NULL || before == NULL)
                    after->next = elem;
            }
            else
            {
                *head = elem;
            }
        }
        else if (before == NULL)
        {
            *head = elem;
        }
    }
}

void remove_duplicates(node_t **head, int (*comparator)(const void*, const void*))
{
    node_t *cur_el = *head;

    while (cur_el)
    {
        node_t *prev_el = cur_el;
        node_t *sec_el = cur_el->next;

        while (sec_el)
        {
            if (!comparator(cur_el->data, sec_el->data))
                remove_element(head, prev_el);
            else
                prev_el = sec_el;

            sec_el = prev_el->next;
        }

        cur_el = cur_el->next;
    }
}

void sort(node_t **head, int (*comparator)(const void*, const void*))
{
    if (head && *head)
    {
        if ((*head)->next)
        {
            node_t *back;
            front_back_split(*head, &back);

            node_t *head_2 = back->next;
            back->next = NULL;

            sort(head, comparator);
            sort(&head_2, comparator);

            *head = sorted_merge(head, &head_2, comparator);
        }
    }
}

void remove_element(node_t **head, node_t *after)
{
    if (head && *head)
    {
        node_t *to_delete;

        if (!after)
        {
            to_delete = *head;
            *head = to_delete->next;
        }
        else
        {
            to_delete = after->next;
            after->next = to_delete->next;
        }

        free(to_delete);
    }
}

void front_back_split(node_t *head, node_t **back)
{
    if (head && back)
    {
        *back = head;
        node_t *tail = head;

        int should_move_back = 0;

        while (tail->next)
        {
            tail = tail->next;

            if (should_move_back++)
                (*back) = (*back)->next;
            else
                should_move_back = 0;
        }
    }
}

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *))
{
    node_t *head;

    if (comparator((*head_a)->data, (*head_b)->data) < 0)
    {
        head = *head_a;
        *head_a = (*head_a)->next;
    }
    else
    {
        head = *head_b;
        *head_b = (*head_b)->next;
    }
    
    node_t *cur = head;

    while (*head_a && *head_b)
    {
        if (comparator((*head_a)->data, (*head_b)->data) < 0)
        {
            cur->next = *head_a;
            *head_a = (*head_a)->next;
        }
        else
        {
            cur->next = *head_b;
            *head_b = (*head_b)->next;
        }

        cur = cur->next;
    }

    while (*head_a)
    {
        cur->next = *head_a;
        *head_a = (*head_a)->next;
        cur = cur->next;
    }

    while (*head_b)
    {
        cur->next = *head_b;
        *head_b = (*head_b)->next;
        cur = cur->next;
    }

    cur->next = NULL;
    return head;
}

void clear(node_t **head)
{
    node_t *node = *head;

    while (node)
    {
        node_t *next = node->next;
        free(node);
        node = next;
    }

    *head = NULL;
}
