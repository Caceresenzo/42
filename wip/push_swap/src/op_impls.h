/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_impls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:15:13 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 12:15:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_IMPLS_H
# define OP_IMPLS_H

# include "../libstack/stack.h"

void	op_swap_a(t_stack *a, t_stack *b);
void	op_swap_b(t_stack *a, t_stack *b);
void	op_swap_x(t_stack *a, t_stack *b);
void	op_push_a(t_stack *a, t_stack *b);
void	op_push_b(t_stack *a, t_stack *b);
void	op_rotate_a(t_stack *a, t_stack *b);
void	op_rotate_b(t_stack *a, t_stack *b);
void	op_rotate_x(t_stack *a, t_stack *b);
void	op_reverse_rotate_a(t_stack *a, t_stack *b);
void	op_reverse_rotate_b(t_stack *a, t_stack *b);
void	op_reverse_rotate_x(t_stack *a, t_stack *b);

void	opi_swap(t_stack *stack);
void	opi_push(t_stack *from, t_stack *to);
void	opi_rotate(t_stack *stack);
void	opi_reverse_rotate(t_stack *stack);

#endif
