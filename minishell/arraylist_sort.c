/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:34:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/03/02 11:34:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

int
	arraylist_sort(t_arrlst *alst, int (*other_cmp)())
{
	int		(*cmp)(void *, void *);
	size_t	index;
	int		swapped;

	if (alst == NULL || alst->size < 2
			|| (!(cmp = other_cmp == NULL ? alst->cmp_method : other_cmp)))
		return (0);
	index = 0;
	while (1)
	{
		index = 0;
		swapped = 0;
		while (index < alst->size - 1)
		{
			if (cmp(alst->items[index], alst->items[index + 1]) > 0)
			{
				ft_swap(&(alst->items[index]), &(alst->items[index + 1]));
				swapped = 1;
			}
			index++;
		}
		if (!swapped)
			break ;
	}
	return (1);
}
