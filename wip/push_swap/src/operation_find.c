/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_find.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:02:22 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 12:02:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "op_impls.h"
#include "op_struct.h"

static t_op
	*operation_storage(void)
{
	static t_op storage[] = {
		{ "sa", op_swap_a },
		{ "sb", op_swap_b },
		{ "ss", op_swap_x },
		{ "pa", op_push_a },
		{ "pb", op_push_b },
		{ "ra", op_rotate_a },
		{ "rb", op_rotate_b },
		{ "rr", op_rotate_x },
		{ "rra", op_reverse_rotate_a },
		{ "rrb", op_reverse_rotate_b },
		{ "rrr", op_reverse_rotate_x },
		{ NULL, NULL },
	};

	return (storage);
}

const t_op
	*operation_find(const char *name)
{
	t_op *op;

	op = operation_storage();
	while (op->name)
	{
		if (strcmp(op->name, name) == 0)
			return (op);
		op++;
	}
	return (NULL);
}
