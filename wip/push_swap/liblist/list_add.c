/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 21:32:02 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/06 21:32:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "list.h"

t_list_node
	*list_add(t_list *list, void *data)
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
