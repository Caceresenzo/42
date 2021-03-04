/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:24:34 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 12:24:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "stack.h"

void
	stack_initialize(t_stack *stack)
{
	if (!stack)
		return ;
	stack->elements = NULL;
	stack->capacity = 0;
	stack->size = 0;
}
