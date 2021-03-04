/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_allocate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:23:17 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 12:23:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

bool
	stack_allocate(t_stack *stack, int capacity)
{
	size_t size;

	stack_free(stack);
	if (capacity <= 0)
		return (true);
	size = capacity * sizeof(int);
	if (!(stack->elements = malloc(size)))
		return (false);
	stack->capacity = capacity;
	memset(stack->elements, 0, size);
	return (true);
}
