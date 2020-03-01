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
	int		ret;
	size_t	sub;

	if (*(*line + 1) == '\"')
	{
		arg_builder_add_char(chrlst, '\"', '\"');
		eval_consume(1, line, consumed, 0);
	}
	else
	{
		ret = eval_escape_backslash(*line, &sub);
		if (ret != -1)
		{
			arg_builder_add_char(chrlst, ret, '\"');
			eval_consume(sub, line, consumed, 0);
		}
	}
}

int
	eval_q_double(char *line, size_t *consumed, t_arrlst *chrlst)
{
	size_t	sub;

	while (*line)
	{
		if (*line == '\\')
			commit_escape(&line, consumed, chrlst);
		else if (*line == '\"')
		{
			*consumed += 1;
			return (0);
		}
		else if (*line == '$')
		{
			sub = 0;
			eval_env_var(line, &sub, chrlst);
			return (eval_consume(sub, &line, consumed, 1));
		}
		else
			arg_builder_add_char(chrlst, *line, '\"');
		*consumed += 1;
		line++;
	}
	return (0);
}
