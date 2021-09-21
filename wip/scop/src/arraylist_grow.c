/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_grow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:34:00 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/21 11:34:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

bool
arraylist_grow(t_arraylist *arraylist, size_t to_capacity)
{
	if (to_capacity <= arraylist->capacity)
		return (true);

	void *vector = calloc(to_capacity, arraylist->type_size);
	if (!vector)
		return (false);

	if (arraylist->vector)
	{
		memcpy(vector, arraylist->vector, arraylist->size * arraylist->type_size);
		free(arraylist->vector);
	}

	arraylist->vector = vector;
	arraylist->capacity = to_capacity;

	return (true);
}

bool
arraylist_grow_auto(t_arraylist *arraylist)
{
	size_t to = (arraylist->capacity + 1) * 2;

	return (arraylist_grow(arraylist, to));
}
