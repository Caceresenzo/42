/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_initialize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 21:42:31 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/06 21:42:31 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "list.h"

void
	list_initialize(t_list *list)
{
	if (!list)
		return ;
	list->size = 0;
	list->first = NULL;
	list->last = NULL;
}
