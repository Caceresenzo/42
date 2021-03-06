/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_push_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:21:04 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 12:21:04 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>

#include "../libstack/stack.h"
#include "push_swap.h"

#define IS_ERROR 1
#define NO_ERROR 0

static int
	quit(t_stack *a, t_stack *b, bool as_err)
{
	stack_free(a);
	stack_free(b);
	if (as_err)
		printf(MSG_ERROR "\n");
	return (as_err);
}

int
	main(int argc, char **argv)
{
	t_stack a;
	t_stack b;

	stack_initialize(&a);
	stack_initialize(&b);
	if (argc == 1)
		return (quit(&a, &b, NO_ERROR));
	if (!stack_allocate(&a, argc - 1) || !stack_allocate(&b, argc - 1))
		return (quit(&a, &b, IS_ERROR));
	if (!stack_fill_from_argv(&a, argc, argv))
		return (quit(&a, &b, IS_ERROR));
	if (!stacks_validate(&a, &b))
		solve(&a, &b);
	return (quit(&a, &b, NO_ERROR));
}
