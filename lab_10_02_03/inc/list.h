#ifndef LIST_H
#define LIST_H

#include "exit_code.h"
#include <stdlib.h>

struct node_t
{
    void *data;
    struct node_t *next;
};

typedef struct node_t node_t;

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *));
void *pop_front(node_t **head);
void *pop_back(node_t **head);
node_t *push_back(node_t *head, node_t **tail, node_t *elem);
void insert(node_t **head, node_t *elem, node_t *before);
size_t list_length(node_t *head);

void remove_duplicates(node_t **head, int (*comparator)(const void *, const void *));

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

void clear(node_t **head, int clear_content);

#endif
