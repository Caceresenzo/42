/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_evaluator_builtin.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:16:56 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 12:16:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	minishell_evaluate_builtin(t_process *process, int sensitive_mode)
{
	t_builtin	*builtin;
	t_arrlst	*arglst;
	int			out;

	arglst = process->arglst;
	if (arglst->size == 0 || process->name == NULL)
		return (0);
	builtin = builtin_match(process->name);
	if (builtin)
	{
		out = process->out_fd == -1 ? OUT : process->out_fd;
		if (sensitive_mode == builtin->sensitive)
			(*(builtin->handler))((t_builtin_param) {
				process->name, arglst->size - 1,
				(char **)(arglst->items), out, ERR
			});
		return (1);
	}
	return (0);
}
