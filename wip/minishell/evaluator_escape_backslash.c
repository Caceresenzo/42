/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator_escape.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:22:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 15:22:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_escaped[255] = {
	['0'] = '\0',
	['a'] = '\a',
	['b'] = '\b',
	['e'] = '\e',
	['f'] = '\f',
	['n'] = '\n',
	['r'] = '\r',
	['t'] = '\t',
	['v'] = '\v',
	['\\'] = '\\',
	['\''] = '\'',
	[' '] = ' '
};

static int
	evaluator_escape_backslash_octal(char *seq, size_t *consumed)
{
	int		len;
	char	*sub;
	int		chr;

	len = ft_isoctal(seq[0]);
	len += len == 1 && ft_isoctal(seq[1]);
	len += len == 2 && ft_isoctal(seq[2]);
	if (len != 3)
		return (-1);
	sub = ft_substr(seq, 0, len);
	chr = sub == NULL ? -1 : ft_atoi_base_insensitive(sub, BASE_OCTAL);
	free(sub);
	*consumed += 1 + len;
	return (chr);
}

static int
	evaluator_escape_backslash_hex(char *seq, size_t *consumed)
{
	int		len;
	char	*sub;
	int		chr;

	seq += 1;
	len = ft_ishex(seq[0]);
	len += len == 1 && ft_ishex(seq[1]);
	sub = ft_substr(seq, 0, len);
	chr = sub == NULL ? -1 : ft_atoi_base_insensitive(sub, BASE_HEX_LOW);
	free(sub);
	*consumed += 2 + len;
	return (chr);
}

int
	eval_escape_backslash(char *seq, size_t *consumed)
{
	char	chr;
	size_t	len;

	if (!*seq)
		return (-1);
	*consumed = 0;
	seq += seq[0] == '\\';
	chr = (int)(0 + g_escaped[(int)*seq]);
	if ((chr != 0 || *seq == '0') && (*consumed += 2))
		return (chr);
	len = ft_strlen(seq);
	if (ft_isoctal(*seq))
		return (evaluator_escape_backslash_octal(seq, consumed));
	if (*seq == 'x')
		return (evaluator_escape_backslash_hex(seq, consumed));
	return (-1);
}
