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
#include <string.h>

#include "../libft/get_next_line.h"
#include "../libft/libft.h"
#include "../libstack/stack.h"
#include "push_swap.h"
#include "push_swap_structs.h"

#define OK 1
#define KO 0
//#define IS_ERROR 1
//#define NO_ERROR 0
#define IS_ERROR ""
#define NO_ERROR NULL

static int
	quit(t_stack *a, t_stack *b, bool ok, const char *err)
{
	stack_free(a);
	stack_free(b);
	if (ok)
		printf(MSG_OK "\n");
	else
	{
		if (err)
			printf(MSG_ERROR ": %s\n", err);
		else
			printf(MSG_KO "\n");
	}
	return (!!err || !ok);
}

static int
	check(t_stack *a, t_stack *b)
{
	char		*line;
	const t_op	*op;
	int			ret;

	line = NULL;
	while ((ret = get_next_line(0, &line)) != -1 && line)
	{
		if (strlen(line) == 0 && ret == 0)
		{
			ft_free_and_release((void**)&line);
			break;
		}
		op = operation_find(line);
//		dprintf(2, "`%s` %p\n", line, op);
		ft_free_and_release((void**)&line);
		if (!op)
			return (quit(a, b, KO, IS_ERROR "unknown op"));
		operation_call(op, a, b);
		if (ret == 0)
			break ;
	}
//	printf("%d\n", ret);
	ft_free_and_release((void**)&line);
	if (ret == -1)
		return (quit(a, b, KO, IS_ERROR "ret == -1"));
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
		return (quit(&a, &b, KO, IS_ERROR "failed malloc"));
	if (!stack_fill_from_argv(&a, argc, argv))
		return (quit(&a, &b, KO, IS_ERROR "failed from argv"));
	return (check(&a, &b));
}
