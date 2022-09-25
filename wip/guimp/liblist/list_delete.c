/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 21:35:08 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/06 21:35:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void
	list_delete(t_list *list, void (*del)(void*))
{
	t_list_node	*node;
	t_list_node	*next;

	if (!list)
		return ;
	node = list->first;
	while (node)
	{
		next = node->next;
		list_node_delete(node, del);
		node = next;
	}
	list_initialize(list);
}
