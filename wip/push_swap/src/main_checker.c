/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:21:04 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 12:21:04 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../libft/get_next_line.h"
#include "../libstack/stack.h"
#include "op_struct.h"
#include "push_swap.h"

#define OK 1
#define KO 0
#define IS_ERROR 1
#define NO_ERROR 0

static int
	quit(t_stack *a, t_stack *b, bool ok, bool as_err)
{
	stack_free(a);
	stack_free(b);
	if (ok)
		printf(MSG_OK "\n");
	else
	{
		if (as_err)
			printf(MSG_ERROR "\n");
		else
			printf(MSG_KO "\n");
	}
	return (as_err || !ok);
}

static int
	check(t_stack *a, t_stack *b)
{
	char		*line;
	const t_op	*op;
	int			ret;

	line = NULL;
	while ((ret = get_next_line(0, &line)) != -1)
	{
		op = operation_find(line);
		ft_free_and_release((void**)&line);
		if (!op)
			return (quit(a, b, KO, IS_ERROR));
		operation_call(op, a, b);
		if (ret == 0)
			break ;
	}
	ft_free_and_release((void**)&line);
	if (ret == -1)
		return (quit(a, b, KO, IS_ERROR));
	if (stacks_validate(a, b))
		return (quit(a, b, OK, NO_ERROR));
	return (quit(a, b, KO, NO_ERROR));
}

int
	main(int argc, char **argv)
{
	t_stack a;
	t_stack b;

	stack_initialize(&a);
	stack_initialize(&b);
	if (argc == 1)
		return (quit(&a, &b, OK, NO_ERROR));
	if (!stack_allocate(&a, argc - 1) || !stack_allocate(&b, argc - 1))
		return (quit(&a, &b, KO, IS_ERROR));
	if (!stack_fill_from_argv(&a, argc, argv))
		return (quit(&a, &b, KO, IS_ERROR));
	return (check(&a, &b));
}
