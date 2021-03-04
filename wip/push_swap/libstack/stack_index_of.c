/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_index_of.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:45:47 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 15:45:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

int
	stack_index_of(t_stack *stack, int x)
{
	int index;

	index = 0;
	while (index < stack->size)
	{
		if (stack->elements[index] == x)
			return (index);
		index++;
	}
	return (-1);
}
