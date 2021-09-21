/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_add_to.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:38:10 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/21 11:38:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

void*
arraylist_add_to(t_arraylist *arraylist)
{
	if (arraylist->capacity == arraylist->size)
		if (!arraylist_grow_auto(arraylist))
			return (NULL);

	return (arraylist_at(arraylist, arraylist->size++));
}
