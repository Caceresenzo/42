/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_reverse_rotate.c                             :+:      :+:    :+:   */
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
	stack_reverse_rotate(t_stack *stack)
{
	long	bottom;
	size_t	size;

	if (stack_size(stack) < 2)
		return ;
	bottom = stack->elements[0];
	size = (stack->size - 1) * sizeof(long);
	memmove(stack->elements, stack->elements + 1, size);
	stack->elements[stack->size - 1] = bottom;
}
