/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:24:34 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 13:24:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "../../libstack/stack.h"

bool
	stack_is_sorted(const t_stack *stack)
{
	int index;
	int size;

	size = stack_size(stack);
	if (size <= 1)
		return (true);
	index = 1;
	while (index < size)
	{
		if (stack_get(stack, index - 1) < stack_get(stack, index))
			return (false);
		index++;
	}
	return (true);
}
