/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_remove_at.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:33:19 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 13:33:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

void
	*arraylist_get(t_arrlst *alst, void *ptr)
{
	ssize_t	index;

	if ((index = arraylist_index_of(alst, ptr)) < 0)
		return (0);
	return (alst->items[index]);
}
