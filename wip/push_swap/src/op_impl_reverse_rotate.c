/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_impl_reverse_rotate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:09:52 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 11:09:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libstack/stack.h"

void
	opi_reverse_rotate(t_stack *x)
{
	stack_reverse_rotate(x);
}

void
	op_reverse_rotate_a(t_stack *a, t_stack *b)
{
	opi_reverse_rotate(a);
	(void)b;
}

void
	op_reverse_rotate_b(t_stack *a, t_stack *b)
{
	opi_reverse_rotate(b);
	(void)a;
}

void
	op_reverse_rotate_x(t_stack *a, t_stack *b)
{
	op_reverse_rotate_a(a, b);
	op_reverse_rotate_b(a, b);
}
