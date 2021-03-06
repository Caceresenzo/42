/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_node_initialize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 21:44:00 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/06 21:44:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "list.h"

void
	list_node_initialize(t_list_node *node, void *data)
{
	if (!node)
		return ;
	node->data = data;
	node->next = NULL;
}
