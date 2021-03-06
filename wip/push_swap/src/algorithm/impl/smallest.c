/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smallest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:53:48 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/06 16:53:48 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "../../../libstack/stack.h"
#include "../../push_swap.h"
#include "../../push_swap_structs.h"

static int
	smallest(t_stack *a)
{
	int sindex;
	int svalue;
	int index;
	int value;

	sindex = stack_size(a) - 1;
	svalue = stack_get(a, sindex);
	index = sindex - 1;
	while (index >= 0)
	{
		if ((value = stack_get(a, index)) < svalue)
		{
			sindex = index;
			svalue = value;
		}
		index--;
	}
	return (sindex);
}

static void
	do_rotations(t_result *result, t_stack *a, t_stack *b, int sindex)
{
	static const char	*ops[2] = { "ra", "rra" };
	int					size;
	int					to;
	bool				invert;

	size = stack_size(a);
	to = size - (sindex + 1);
	if ((invert = (to > (size / 2))))
		to = size - to;
	while (to--)
		algorithm_action(result, ops[invert], a, b);
}

bool
	algo_smallest(t_result *result, t_stack *a, t_stack *b)
{
	while (stack_size(a) > 2)
	{
		if (stack_is_sorted(a))
			break ;
		if (stack_get(a, 0) < stack_get(a, 1))
			algorithm_action(result, "sa", a, b);
		if (stack_is_sorted(a))
			break ;
		do_rotations(result, a, b, smallest(a));
		algorithm_action(result, "pb", a, b);
	}
	if (stack_size(a) == 2 && stack_get(a, 0) < stack_get(a, 1))
		algorithm_action(result, "ra", a, b);
	while (!stack_empty(b))
		algorithm_action(result, "pa", a, b);
	return (true);
}
