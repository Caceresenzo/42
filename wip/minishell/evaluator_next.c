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
		if (ft_isquote(*(*line + 1)))
		{
			arg_builder_add_char(chrlst, *(*line + 1), 0);
			return (eval_consume(2, line, consumed, 1));
		}
		else
			return (eval_consume(1, line, consumed, 1));
	}
	else if (**line == '\'')
	{
		eval_q_single(*line + 1, &sub, chrlst);
		return (eval_consume(sub + 1, line, consumed, 1));
	}
	else if (**line == '\"')
	{
		eval_q_double(*line + 1, &sub, chrlst);
		return (eval_consume(sub + 1, line, consumed, 1));
	}
	return (commit2(line, consumed, chrlst, sub));
}

static inline int
	kind(int used, int kind)
{
	return (used ? TOKEN_KIND_STRING : kind);
}

int
	eval_next(char *line, size_t *consumed, t_arrlst *chrlst)
{
	int		used;

	used = 0;
	while (*line)
	{
		used |= commit(&line, consumed, chrlst, 0);
		if (ft_iswspace(*line))
			return (TOKEN_KIND_STRING);
		else if (*line == '>' && *(line + 1) == '>')
			return (kind(used, TOKEN_KIND_APPEND));
		else if (*line == '<')
			return (kind(used, TOKEN_KIND_INPUT));
		else if (*line == '>')
			return (kind(used, TOKEN_KIND_OUTPUT));
		else if (*line == '|')
			return (kind(used, TOKEN_KIND_PIPE));
		else if (*line == ';')
			return (kind(used, TOKEN_KIND_SEMICOLON));
		else
		{
			arg_builder_add_char(chrlst, *line, 0);
			used |= eval_consume(1, &line, consumed, 1);
		}
	}
	return (kind(used, 0));
}
