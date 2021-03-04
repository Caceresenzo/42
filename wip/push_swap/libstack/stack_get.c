/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:44:14 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 11:44:14 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

int
	stack_get(const t_stack *stack, int index)
{
	if (!stack || index < 0 || index >= stack->size)
		return (0);
	return (stack->elements[index]);
}
