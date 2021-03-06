/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:59:54 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/06 15:59:54 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../liblist/list.h"
#include "../../libstack/stack.h"
#include "../push_swap.h"
#include "../push_swap_structs.h"

static bool
	do_solving(
		const t_algorithm *algorithm,
		t_result *result,
		t_stack *a,
		t_stack *b)
{
	t_stack a_copy;
	t_stack b_copy;
	bool	success;

	if (!algorithm)
		return (true);
	stack_initialize(&a_copy);
	stack_initialize(&b_copy);
	stack_copy(a, &a_copy);
	stack_copy(b, &b_copy);
	list_initialize(&result->operations);
	result->algorithm = NULL;
	if ((success = algorithm_run(algorithm, result, &a_copy, &b_copy)))
		result->algorithm = algorithm;
	result->success = success;
	result->count = list_size(&result->operations);
	stack_free(&a_copy);
	stack_free(&b_copy);
	return (success);
}

t_result
	*delete_all(t_result *results)
{
	t_result *result;

	result = results;
	while (result->algorithm)
	{
		list_delete(&(result->operations), NULL);
		result++;
	}
	free(results);
	return (NULL);
}

t_result
	*solve_all(t_stack *a, t_stack *b)
{
	t_result	*results;
	int			count;
	int			index;

	count = algorithm_storage_size();
	if (!(results = calloc(count + 1, sizeof(t_result))))
		return (NULL);
	index = 0;
	while (index < count)
	{
		if (!do_solving(algorithm_storage() + index, results + index, a, b))
			return (delete_all(results));
		index++;
	}
	do_solving(NULL, results + index, NULL, NULL);
	return (results);
}

static void
	print_solution(void *name)
{
	printf("%s\n", (char*)name);
}

void
	solve(t_stack *a, t_stack *b)
{
	t_result *results;
	t_result *result;
	t_result *best;

	if ((results = solve_all(a, b)))
	{
		result = results;
		while (result->algorithm)
		{
			if (!best || best->count > result->count)
				best = result;
			dprintf(2, "%s: %ld,  ", result->algorithm->name, result->count);
			result++;
		}
		dprintf(2, "\n");
		list_for_each(&(best->operations), print_solution);
	}
	delete_all(results);
}
