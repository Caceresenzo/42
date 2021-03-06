/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:07:45 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 11:07:45 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdbool.h>

typedef struct	s_stack
{
	int			*elements;
	int			capacity;
	int			size;
}				t_stack;

void			stack_initialize(t_stack *stack);

bool			stack_allocate(t_stack *stack, int capacity);
void			stack_free(t_stack *stack);

bool			stack_copy(t_stack *from, t_stack *to);
t_stack			*stack_duplicate(t_stack *stack);

int				stack_size(const t_stack *stack);
bool			stack_empty(const t_stack *stack);

int				stack_top(const t_stack *stack);
int				stack_get(const t_stack *stack, int index);

int				stack_pop(t_stack *stack);
void			stack_push(t_stack *stack, int x);

void			stack_rotate(t_stack *stack);
void			stack_reverse_rotate(t_stack *stack);

int				stack_index_of(t_stack *stack, int x);

void			stack_print(t_stack *stack);

#endif
