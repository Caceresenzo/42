/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:44:07 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 11:44:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void
	stack_push(t_stack *stack, int x)
{
	if (!stack || stack->size == stack->capacity)
		return ;
	stack->elements[stack->size++] = x;
}
