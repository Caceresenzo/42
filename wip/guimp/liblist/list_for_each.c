/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_for_each.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 23:44:54 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/06 23:44:54 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void
	list_for_each(t_list *list, void (*consumer)(void*))
{
	t_list_node	*node;

	if (!list || !consumer)
		return ;
	node = list->first;
	while (node)
	{
		(*(consumer))(node->data);
		node = node->next;
	}
}
