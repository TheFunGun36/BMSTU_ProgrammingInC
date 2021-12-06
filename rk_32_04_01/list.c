#include "list.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

void list_initialize(list_t *list)
{
	memset(list, 0, sizeof(list_t));
}

int list_push_back(list_t *list, void *val)
{
	int exit_code = LIST_OK;
	
	node_t *new_element = calloc(1, sizeof(node_t));
	
	if (new_element)
	{
		if (list->end)
		{
			new_element->prev = list->end;
			list->end->next = new_element;
		}
		else
		{
			list->begin = new_element;
		}
		
		list->end = new_element;
		new_element->val = val;
		list->length++;
	}
	else
	{
		exit_code = LIST_NO_MEMORY;
	}
	
	return exit_code;
}

int list_push_front(list_t *list, void *val);

void *list_pop_back(list_t *list)
{
	void *result = NULL;
	
	if (list->end)
	{
		result = list->end->val;
		
		list->end = list->end->prev;
		
		if (list->end)
		{
			free(list->end->next);
			list->end->next = NULL;
		}
		else
		{
			list->begin = NULL;
		}
		
		list->length--;
	}
	
	return result;
}

void *list_pop_front(list_t *list)
{
	void *result = NULL;
	
	if (list->begin)
	{
		result = list->begin->val;
		
		list->begin = list->begin->next;
		
		if (list->begin)
		{
			free(list->begin->prev);
			list->begin->prev = NULL;
		}
		else
		{
			list->end = NULL;
		}
			
		list->length--;
	}
	
	return result;
}

void *list_sort(list_t *list, int (*comp)(void *,void *));