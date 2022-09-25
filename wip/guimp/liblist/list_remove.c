/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 21:35:08 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/06 21:35:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

bool
	list_remove(t_list *list, void *data, void (*del)(void*))
{
	t_list_node	*node;
	t_list_node	*next;
	t_list_node	*previous;

	if (!list)
		return (false);
	node = list->first;
	previous = NULL;
	while (node)
	{
		next = node->next;
		if (node->data == data)
		{
			list->size -= 1;
			if (previous)
				previous->next = next;
			else
				list->first = next;
			if (list->last == node)
				list->last = previous;
			list_node_delete(node, del);
			return (true);
		}
		previous = node;
		node = next;
	}
	return (false);
}
