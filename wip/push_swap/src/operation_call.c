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

#include "../libstack/stack.h"
#include "op_struct.h"

void
	operation_call(const t_op *op, t_stack *a, t_stack *b)
{
	(*(op->operation))(a, b);
}
