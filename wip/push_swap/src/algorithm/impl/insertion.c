/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   by_smallest.c                                      :+:      :+:    :+:   */
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

/*
** . def sort_stack(a):
** .	res_stack = deque()
** .
** .	# We keep res_stack always sorted
** .	while len(a) > 0:
** .		aTop = a.pop()
** .
** .		while True:
** .			if len(b) == 0:
** .				b.append(aTop)
** .				break
** .
** .			bTop = b.pop()
** .			if bTop <= aTop:
** .				b.append(bTop)
** .				b.append(aTop)
** .				break
** .			else:
** .				a.append(bTop)
** .
** .	return b
** .
*/

static bool
	do_move(t_result *result, t_stack *a, t_stack *b)
{
	while (true)
	{
		if (stack_empty(b))
		{
			if (!algorithm_action(result, "pb", a, b))
				return (false);
			break ;
		}
		if (stack_top(b) <= stack_top(a))
		{
			if (!algorithm_action(result, "pb", a, b))
				return (false);
			break ;
		}
		else
		{
			if (!algorithm_action(result, "pa", a, b)
					|| !algorithm_action(result, "sa", a, b))
				return (false);
		}
	}
	return (true);
}

bool
	algo_insertion(t_result *result, t_stack *a, t_stack *b)
{
	while (!stack_empty(a))
	{
		if (!do_move(result, a, b))
			return (false);
	}
	while (!stack_empty(b))
	{
		if (!algorithm_action(result, "pa", a, b))
			return (false);
	}
	return (true);
}
