/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:25:59 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 11:25:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "stack.h"

bool
	stack_empty(const t_stack *stack)
{
	if (!stack)
		return (false);
	return (stack->size == 0);
}
