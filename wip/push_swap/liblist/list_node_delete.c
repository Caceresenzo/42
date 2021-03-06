/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_node_delete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 21:52:09 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/06 21:52:09 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "list.h"

void
	list_node_delete(t_list_node *node, void (*del)(void*))
{
	if (!node)
		return ;
	if (del)
		(*(del))(node->data);
	free(node);
}
