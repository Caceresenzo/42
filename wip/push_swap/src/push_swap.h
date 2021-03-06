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
# include "push_swap_structs.h"

# define MSG_OK "OK"
# define MSG_KO "KO"
# define MSG_ERROR "Error"

typedef const t_algorithm	t_calgo;
typedef const char	t_cchar;

const t_op	*operation_find(const char *name);
void		operation_call(const t_op *op, t_stack *a, t_stack *b);

t_calgo		*algorithm_storage(void);
int			algorithm_storage_size(void);
bool		algorithm_run(t_calgo *al, t_result *r, t_stack *a, t_stack *b);
bool		algorithm_action(t_result *r, t_cchar *op, t_stack *a, t_stack *b);

void		solve(t_stack *a, t_stack *b);

void		op_swap_a(t_stack *a, t_stack *b);
void		op_swap_b(t_stack *a, t_stack *b);
void		op_swap_x(t_stack *a, t_stack *b);
void		op_push_a(t_stack *a, t_stack *b);
void		op_push_b(t_stack *a, t_stack *b);
void		op_rotate_a(t_stack *a, t_stack *b);
void		op_rotate_b(t_stack *a, t_stack *b);
void		op_rotate_x(t_stack *a, t_stack *b);
void		op_reverse_rotate_a(t_stack *a, t_stack *b);
void		op_reverse_rotate_b(t_stack *a, t_stack *b);
void		op_reverse_rotate_x(t_stack *a, t_stack *b);

bool		algo_smallest(t_result *result, t_stack *a, t_stack *b);
bool		algo_insertion(t_result *result, t_stack *a, t_stack *b);

bool		stack_fill_from_argv(t_stack *stack, int argc, char **argv);
bool		stack_is_sorted(const t_stack *stack);
bool		stacks_validate(const t_stack *a, const t_stack *b);

#endif
