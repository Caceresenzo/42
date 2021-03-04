/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_top.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:44:14 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 11:44:14 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

int
	stack_top(const t_stack *stack)
{
	if (!stack || stack->size == 0)
		return (0);
	return (stack->elements[stack->size - 1]);
}
