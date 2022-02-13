/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:38:37 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/13 18:38:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void
list_initialize(t_list *list)
{
	if (!list)
		return;
	list->size = 0;
	list->first = NULL;
	list->last = NULL;
}

t_list_node*
list_add(t_list *list, void *data)
{
	t_list_node *node;

	if (!list)
		return (NULL);
	if ((node = malloc(sizeof(t_list_node))))
	{
		list_node_initialize(node, data);
		if (!list->first)
		{
			list->first = node;
			list->last = node;
		}
		else
		{
			list->last->next = node;
			list->last = node;
		}
		list->size++;
	}
	return (node);
}

long
list_size(t_list *list)
{
	if (!list)
		return (-1);
	return (list->size);
}

void
list_for_each(t_list *list, t_list_node_consumer consumer)
{
	t_list_node *node;

	if (!list || !consumer)
		return;
	node = list->first;
	while (node)
	{
		consumer(node->data);
		node = node->next;
	}
}

void
list_delete(t_list *list, t_list_node_consumer del)
{
	t_list_node *node;
	t_list_node *next;

	if (!list)
		return;
	node = list->first;
	while (node)
	{
		next = node->next;
		list_node_delete(node, del);
		node = next;
	}
	list_initialize(list);
}

void
list_node_initialize(t_list_node *node, void *data)
{
	if (!node)
		return;
	node->data = data;
	node->next = NULL;
}

t_list_node*
list_node_next(t_list_node *node)
{
	if (!node)
		return (NULL);
	return (node->next);
}

void
list_node_delete(t_list_node *node, t_list_node_consumer del)
{
	if (!node)
		return;
	if (del)
		del(node->data);
	free(node);
}

static void
swap_void(void **a, void **b)
{
	void *c = *a;
	*a = *b;
	*b = c;
}

void
list_sort(t_list *list, t_list_node_compare comparator, bool reverse)
{
	if (!list || !comparator)
		return;

	t_list_node *current = list->first;

	while (current && current->next)
	{
		t_list_node *next = current->next;

		while (next)
		{
			int diff = comparator(current->data, next->data);

			if ((reverse && diff < 0) || (!reverse && diff > 0))
				swap_void(&current->data, &next->data);

			next = next->next;
		}

		current = current->next;
	}
}
