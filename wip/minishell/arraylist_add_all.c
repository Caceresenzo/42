/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:29:56 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 18:29:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

int
	arraylist_add_all(t_arrlst *dstlst, t_arrlst *srclst)
{
	size_t	index;

	if (dstlst == NULL || srclst == NULL || dstlst->items == NULL
			|| srclst->size == 0 || !arraylist_grow(dstlst, srclst->size))
		return (0);
	index = 0;
	while (index < srclst->size)
	{
		if (!arraylist_add(dstlst, srclst->items[index]))
			return (0);
		index++;
	}
	return (1);
}
