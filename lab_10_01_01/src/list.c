#include "list.h"
#include <stdlib.h>

#define LIST_INC(list) ((list) = (list)->next)

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
                LIST_INC(head);
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
                LIST_INC(pre_tail);

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
    if (*head)
    {
        if (before != *head)
        {
            node_t *after = *head;

            while (after->next && after->next != before)
                LIST_INC(after);

            if (after->next == before)
            {
                after->next = elem;
                elem->next = before;
            }
        }
        else
        {
            *head = elem;
            elem->next = before;
        }
    }
    else if (!before)
    {
        *head = elem;
        elem->next = before;
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

        LIST_INC(cur_el);
    }
}

node_t *sort(node_t *head, int (*comparator)(const void*, const void*))
{
    if (head && comparator)
    {
        if (head->next)
        {
            node_t *back;
            front_back_split(head, &back);

            head = sort(head, comparator);
            back = sort(back, comparator);

            head = sorted_merge(&head, &back, comparator);
        }
    }

    return head;
}

void remove_element(node_t **head, node_t *after)
{
    if (head && *head)
    {
        node_t *to_delete;

        if (!after)
        {
            to_delete = *head;
            LIST_INC(*head);
        }
        else
        {
            to_delete = after->next;
            LIST_INC(after->next);
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
            {
                (*back) = (*back)->next;
                should_move_back = 0;
            }
        }

        node_t *new_head = (*back)->next;
        (*back)->next = NULL;
        *back = new_head;
    }
}

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *))
{
    node_t *head = NULL;
    
    if (head_a && head_b && *head_a && *head_b)
    {
        if (comparator((*head_a)->data, (*head_b)->data) > 0)
        {
            node_t **tmp = head_a;
            head_a = head_b;
            head_b = tmp;
        }
        
        head = *head_a;
        LIST_INC(*head_a);
    }
    else
    {
        if (head_a && *head_a)
        {
            head = *head_a;
            LIST_INC(*head_a);
        }
        else if (head_b && *head_b)
        {
            node_t **tmp = head_a;
            head_a = head_b;
            head_b = tmp;
            head = *head_a;
            LIST_INC(*head_a);
        }
    }

    if (head_a)
        *head_a = NULL;

    node_t *node;
    if (head)
    {
        for (node = head; node->next && head_b && *head_b; LIST_INC(node))
        {
            if (comparator(node->next->data, (*head_b)->data) > 0)
            {
                node_t *new_node = *head_b;
                LIST_INC(*head_b);
                new_node->next = node->next;
                node->next = new_node;
            }
        }
    }

    if (head_b && *head_b)
    {
        node->next = *head_b;
    }

    if (head_b)
        *head_b = NULL;

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
