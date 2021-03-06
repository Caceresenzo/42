/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 22:30:15 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/06 22:30:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <string.h>

#include "stack.h"

bool
	stack_copy(t_stack *from, t_stack *to)
{
	if (!from || !to)
		return (NULL);
	if (!stack_allocate(to, from->capacity))
	{
		stack_free(to);
		return (false);
	}
	memcpy(to->elements, from->elements, sizeof(int) * from->capacity);
	to->size = from->size;
	return (true);
}
