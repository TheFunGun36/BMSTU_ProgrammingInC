#ifndef LIST_H
#define LIST_H

#define LIST_OK 0
#define LIST_NO_MEMORY 1

struct node_t
{
	struct node_t *next;
	struct node_t *prev;
	void *val;
};

typedef struct node_t node_t;

typedef struct
{
	struct node_t *begin;
	struct node_t *end;
	int length;
} list_t;

void list_initialize(list_t *list);

int list_push_back(list_t *list, void *val);
int list_push_front(list_t *list, void *val);

void *list_pop_back(list_t *list);
void *list_pop_front(list_t *list);

void *list_sort(list_t *list, int (*comp)(void *,void *));

#endif
