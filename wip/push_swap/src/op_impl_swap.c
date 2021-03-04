/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_impl_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:09:52 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 11:09:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libstack/stack.h"

void
	opi_swap(t_stack *x)
{
	long a;
	long b;

	if (stack_size(x) < 2)
		return ;
	a = stack_pop(x);
	b = stack_pop(x);
	stack_push(x, a);
	stack_push(x, b);
}

void
	op_swap_a(t_stack *a, t_stack *b)
{
	opi_swap(a);
	(void)b;
}

void
	op_swap_b(t_stack *a, t_stack *b)
{
	opi_swap(b);
	(void)a;
}

void
	op_swap_x(t_stack *a, t_stack *b)
{
	op_swap_a(a, b);
	op_swap_b(a, b);
}
