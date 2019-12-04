/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_comp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:32:43 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 16:32:43 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	i_ft_sort_comp_compute_gap(int gap)
{
	gap = (gap * 10) / 13;
	if (gap == 9 || gap == 10)
		gap = 11;
	if (gap < 1)
		gap = 1;
	return (gap);
}

void
	ft_sort_comp(int *order, double *dist, int amount)
{
	int		gap;
	int		swapped;
	int		index;
	int		jndex;

	gap = amount;
	swapped = 0;
	while (gap > 1 || swapped)
	{
		gap = i_ft_sort_comp_compute_gap(gap);
		swapped = 0;
		index = 0;
		while (index < amount - gap)
		{
			jndex = index + gap;
			if (dist[index] < dist[jndex])
			{
				ft_swap_double(dist + index, dist + jndex);
				ft_swap_int(order + index, order + jndex);
				swapped = 1;
			}
			index++;
		}
	}
}
