/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:49:29 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 11:49:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <string.h>

#include "stack.h"

void
	stack_rotate(t_stack *stack)
{
	long	top;
	size_t	size;

	if (stack_size(stack) < 2)
		return ;
	top = stack_top(stack);
	size = (stack->size - 1) * sizeof(int);
	memmove(stack->elements + 1, stack->elements, size);
	stack->elements[0] = top;
}
