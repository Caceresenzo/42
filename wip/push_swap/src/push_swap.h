/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:16:40 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 11:16:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>

# include "../libstack/stack.h"
# include "op_struct.h"

# define MSG_OK "OK"
# define MSG_KO "KO"
# define MSG_ERROR "Error"

const t_op	*operation_find(const char *name);
void		operation_call(const t_op *op, t_stack *a, t_stack *b);

bool		stack_fill_from_argv(t_stack *stack, int argc, char **argv);
bool		stacks_validate(const t_stack *a, const t_stack *b);

#endif
