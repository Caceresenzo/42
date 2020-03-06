/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator_quote_double.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:22:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 15:22:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	commit_escape(char **line, size_t *consumed, t_arrlst *chrlst)
{
	char	n;

	if ((n = *(*line + 1)) == Q_DOUBLE || n == '\\' || n == '$')
	{
		arg_builder_add_char(chrlst, *(*line + 1), Q_DOUBLE);
		eval_consume(1, line, consumed, 0);
	}
	else
		arg_builder_add_char(chrlst, '\\', Q_DOUBLE);
}

int
	eval_q_double(char *line, size_t *consumed, t_arrlst *chrlst)
{
	size_t	sub;

	if (*line == Q_DOUBLE)
		eval_consume(1, &line, consumed, 0);
	while (*line)
	{
		if (*line == '\\')
			commit_escape(&line, consumed, chrlst);
		else if (*line == Q_DOUBLE)
			return (eval_consume(1, &line, consumed, 0));
		else if (*line == '$')
		{
			sub = 0;
			eval_env_var(line, &sub, chrlst);
			eval_consume(sub, &line, consumed, 1);
			continue ;
		}
		else
			arg_builder_add_char(chrlst, *line, Q_DOUBLE);
		eval_consume(1, &line, consumed, 0);
	}
	return (0);
}
