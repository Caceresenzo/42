/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 12:16:14 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/06 12:16:14 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void
	ft_swap_void(void **a, void **b)
{
	void *c;

	c = *a;
	*a = *b;
	*b = c;
}

void
	ft_lstsort(t_list **begin_list, int (*cmp)(void *, void *))
{
	t_list	*current;
	t_list	*end;
	int		swapped;

	if (*begin_list == 0)
		return ;
	swapped = 1;
	end = 0;
	while (swapped)
	{
		swapped = 0;
		current = *begin_list;
		while (1)
		{
			if (current->next == end)
				break ;
			if ((*cmp)(current->content, current->next->content) > 0)
			{
				ft_swap_void(&(current->content), &(current->next->content));
				swapped = 1;
			}
			current = current->next;
		}
		end = current;
	}
}
