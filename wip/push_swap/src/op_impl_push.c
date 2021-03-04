/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_impl_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:09:52 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 11:09:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libstack/stack.h"

void
	opi_push(t_stack *from, t_stack *to)
{
	if (stack_size(from) < 1)
		return ;
	stack_push(to, stack_pop(from));
}

void
	op_push_a(t_stack *a, t_stack *b)
{
	opi_push(b, a);
}

void
	op_push_b(t_stack *a, t_stack *b)
{
	opi_push(a, b);
}
