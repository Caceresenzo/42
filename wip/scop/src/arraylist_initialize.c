/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_initialize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:29:26 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/21 11:29:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

bool
arraylist_initialize(t_arraylist *arraylist, size_t initial_capacity, size_t type_size)
{
	if (!(arraylist->vector = calloc(initial_capacity, type_size)))
		return (false);

	arraylist->capacity = initial_capacity;
	arraylist->size = 0;
	arraylist->type_size = type_size;

	return (true);
}
