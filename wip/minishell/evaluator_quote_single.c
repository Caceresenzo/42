/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator_quote_single.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:59:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/26 11:59:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	commit(char **line, size_t *consumed, t_arrlst *chrlst)
{
	int		ret;
	size_t	sub;

	if (**line == '\\')
	{
		if (*(*line + 1) == '\'')
		{
			arg_builder_add_char(chrlst, '\\', '\'');
			return (eval_consume(2, line, consumed, 0));
		}
		else
		{
			ret = eval_escape_backslash(*line, &sub);
			if (ret != -1)
			{
				arg_builder_add_char(chrlst, ret, '\'');
				*consumed += sub;
				*line += *consumed;
			}
		}
		return (1);
	}
	return (2);
}

int
	eval_q_single(char *line, size_t *consumed, t_arrlst *chrlst)
{
	int		ret;

	while (*line)
	{
		ret = commit(&line, consumed, chrlst);
		if (ret == 0)
			return (0);
		else if (ret == 2)
		{
			if (*line == '\'')
				return (eval_consume(1, &line, consumed, 0));
			else
				arg_builder_add_char(chrlst, *line, '\'');
		}
		eval_consume(1, &line, consumed, 0);
	}
	return (0);
}
