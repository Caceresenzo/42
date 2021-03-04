/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:54:24 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 15:54:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "stack.h"

void
	stack_print(t_stack *stack)
{
	int index;

	printf("stack(size=%d, capacity=%d) -- %p\n", stack->size,
		stack->capacity, stack);
	index = 0;
	while (index < stack->capacity)
	{
		printf("[%d] = %d\n", index, stack->elements[index]);
		index++;
	}
	printf("\n");
}
