/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:02:22 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 12:02:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>

#include "../../liblist/list.h"
#include "../../libstack/stack.h"
#include "../push_swap.h"
#include "../push_swap_structs.h"

bool
	algorithm_action(t_result *result, const char *name, t_stack *a, t_stack *b)
{
	const t_op	*op;

	op = operation_find(name);
	if (!op)
	{
		printf("WARNING: no action named `%s`\n", name);
		return (false);
	}
	if (result && !list_add(&(result->operations), (void*)name))
		return (false);
	operation_call(op, a, b);
	return (true);
}
