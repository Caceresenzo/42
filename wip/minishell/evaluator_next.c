/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator_next.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 10:33:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/21 10:33:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	commit2(char **line, size_t *consumed, t_arrlst *chrlst, size_t sub)
{
	if (**line == '~')
	{
		eval_tilde(*line, &sub, chrlst);
		return (eval_consume(sub, line, consumed, 1));
	}
	else if (**line == '$')
	{
		eval_env_var(*line, &sub, chrlst);
		return (eval_consume(sub, line, consumed, 1));
	}
	return (0);
}

static int
	commit(char **line, size_t *consumed, t_arrlst *chrlst, size_t sub)
{
	if (**line == '\\')
	{
		if (*(*line + 1) != '\0')
		{
			arg_builder_add_char(chrlst, *(*line + 1), 0);
			eval_consume(1, line, consumed, 1);
		}
		return (eval_consume(1, line, consumed, 1));
	}
	else if (**line == Q_SINGLE)
	{
		eval_q_single(*line, &sub, chrlst);
		return (eval_consume(sub, line, consumed, 1));
	}
	else if (**line == Q_DOUBLE)
	{
		eval_q_double(*line, &sub, chrlst);
		return (eval_consume(sub, line, consumed, 1));
	}
	return (commit2(line, consumed, chrlst, sub));
}

static inline int
	kind(int used, int kind)
{
	return (used ? TOKEN_KIND_STRING : kind);
}

static int
	loop(char **line, size_t *consumed, t_arrlst *chrlst, int *used)
{
	int		used_this_time;

	used_this_time = commit(line, consumed, chrlst, 0);
	*used |= used_this_time;
	if (ft_iswspace(**line))
		return (TOKEN_KIND_STRING);
	else if (**line == '>' && *(*line + 1) == '>')
		return (kind(*used, TOKEN_KIND_APPEND));
	else if (**line == '<')
		return (kind(*used, TOKEN_KIND_INPUT));
	else if (**line == '>')
		return (kind(*used, TOKEN_KIND_OUTPUT));
	else if (**line == '|')
		return (kind(*used, TOKEN_KIND_PIPE));
	else if (**line == ';')
		return (kind(*used, TOKEN_KIND_SEMICOLON));
	else if (!used_this_time)
	{
		arg_builder_add_char(chrlst, **line, 0);
		*used |= eval_consume(1, line, consumed, 1);
	}
	return (-1);
}

int
	eval_next(char *line, size_t *consumed, t_arrlst *chrlst)
{
	int		used;
	int		ret;

	used = 0;
	while (*line)
	{
		if ((ret = loop(&line, consumed, chrlst, &used)) != -1)
			return (ret);
	}
	return (kind(used, 0));
}
