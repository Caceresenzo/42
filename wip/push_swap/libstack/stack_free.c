/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:27:33 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 12:27:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "stack.h"

void
	stack_free(t_stack *stack)
{
	if (!stack)
		return ;
	free(stack->elements);
	stack_initialize(stack);
}
