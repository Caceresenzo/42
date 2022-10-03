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

long
	list_size(t_list *list)
{
	if (!list)
		return (-1);
	return (list->size);
}

long
	list_size_filtered(t_list *list, bool (*predicate)(void*), bool negate)
{
	long size;
	t_list_node	*node;

	if (!list)
		return (-1);
	size = 0;
	node = list->first;
	while (node)
	{
		if (predicate(node->data) != negate)
			++size;
		node = node->next;
	}
	return (size);
}
