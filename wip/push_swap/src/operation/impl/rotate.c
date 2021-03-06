/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:09:52 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 11:09:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libstack/stack.h"

void
	opi_rotate(t_stack *x)
{
	stack_rotate(x);
}

void
	op_rotate_a(t_stack *a, t_stack *b)
{
	opi_rotate(a);
	(void)b;
}

void
	op_rotate_b(t_stack *a, t_stack *b)
{
	opi_rotate(b);
	(void)a;
}

void
	op_rotate_x(t_stack *a, t_stack *b)
{
	op_rotate_a(a, b);
	op_rotate_b(a, b);
}
