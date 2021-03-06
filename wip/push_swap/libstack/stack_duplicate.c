/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_duplicate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 22:30:15 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/06 22:30:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "stack.h"

t_stack
	*stack_duplicate(t_stack *stack)
{
	t_stack *copy;

	if (!stack)
		return (NULL);
	if (!(copy = malloc(sizeof(t_stack))))
		return (NULL);
	stack_initialize(copy);
	if (!stack_copy(stack, copy))
	{
		free(copy);
		return (NULL);
	}
	return (copy);
}
