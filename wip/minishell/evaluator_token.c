/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:26:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 17:26:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	ignore_wspace(size_t *consumed, char **line)
{
	while (ft_iswspace(**line))
		eval_consume(1, line, consumed, 0);
}

static t_token
	*handle(int kind, size_t *consumed, char **line)
{
	eval_consume(1, line, consumed, 0);
	if (kind >= TOKEN_KIND_INPUT && kind <= TOKEN_KIND_APPEND)
	{
		if (kind == TOKEN_KIND_APPEND)
			eval_consume(1, line, consumed, 0);
		return (token_create_io(kind));
	}
	else if (kind == TOKEN_KIND_PIPE)
		return (token_create(TOKEN_KIND_PIPE, NULL));
	else if (kind == TOKEN_KIND_SEMICOLON)
		return (token_create(TOKEN_KIND_SEMICOLON, NULL));
	return (NULL);
}

static t_token
	*next_token(char *line, size_t *consumed)
{
	int			ret;
	size_t		sub;
	t_arrlst	chrlst;
	t_token		*tok;

	sub = 0;
	ignore_wspace(&sub, &line);
	arg_builder_initialize(&chrlst);
	ret = eval_next(line, &sub, &chrlst);
	if (ret == TOKEN_KIND_STRING)
		tok = token_create(ret, arg_builder_build(&chrlst));
	else
		tok = handle(ret, &sub, &line);
	arg_builder_finalize(&chrlst);
	line += sub;
	ignore_wspace(&sub, &line);
	*consumed += sub;
	return (tok);
}

int
	eval_tokens(t_arrlst *tokenlst, char *line, size_t *consumed)
{
	t_token		*tok;
	size_t		sub;

	while (*line)
	{
		ignore_wspace(consumed, &line);
		sub = 0;
		tok = next_token(line, &sub);
		eval_consume(sub, &line, consumed, 0);
		ignore_wspace(consumed, &line);
		if (tok != NULL)
		{
			arraylist_add(tokenlst, tok);
			if (tok->kind == TOKEN_KIND_SEMICOLON)
				break ;
		}
	}
	return (1);
}
