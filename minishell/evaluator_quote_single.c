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

int
	eval_q_single(char *line, size_t *consumed, t_arrlst *chrlst)
{
	int		is;

	if (*line == Q_SINGLE)
		eval_consume(1, &line, consumed, 0);
	while (*line)
	{
		if (!(is = *line == Q_SINGLE))
			arg_builder_add_char(chrlst, *line, Q_SINGLE);
		eval_consume(1, &line, consumed, 0);
		if (is)
			break ;
	}
	return (0);
}
