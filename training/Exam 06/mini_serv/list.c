#include <stdio.h>
#include <stdlib.h>

#include "mini_serv.h"

t_list*
list_add(t_list **lst, void *data)
{
	t_list *node = (t_list*)malloc(sizeof(t_list));

	if (node)
	{
		node->data = data;
		node->next = NULL;

		if (*lst)
		{
			t_list *x = *lst;
			while (x->next)
				x = x->next;

			x->next = node;
		}
		else
			*lst = node;
	}

	return (node);
}

void
list_clear(t_list **lst, void (*del)(void*))
{
	t_list *node = *lst;

	while (node)
	{
		if (del)
			(*del)(node->data);

		t_list *x = node;
		node = node->next;
		free(x);
	}

	*lst = NULL;
}

void
list_delete_first(t_list **lst, void *data, void (*del)(void*))
{
	t_list *node = *lst;
	t_list *previous = NULL;

	while (node)
	{
		if (node->data == data)
		{
			if (del)
				(*del)(node->data);

			if (previous)
				previous->next = node->next;
			else
				*lst = node->next;

			free(node);

			break;
		}

		previous = node;
		node = node->next;
	}
}
