/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:33:19 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 13:33:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

int
	arraylist_remove(t_arrlst *alst, void *ptr, void (*free_fct)())
{
	ssize_t	index;
	size_t	pos;

	if ((index = arraylist_index_of(alst, ptr)) < 0)
		return (0);
	pos = 0 + index;
	return (arraylist_remove_at(alst, pos, free_fct));
}
