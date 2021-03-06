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

t_list_node
	*list_node_next(t_list_node *node)
{
	if (!node)
		return (NULL);
	return (node->next);
}
