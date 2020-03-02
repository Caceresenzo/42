/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:57:36 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 18:57:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	eval_tilde(char *line, size_t *consumed, t_arrlst *chrlst)
{
	char	*home;

	if (*line != '~')
		return (0);
	*consumed += 1;
	home = home_get_cache();
	if (home == NULL)
		arg_builder_add_char(chrlst, '~', 0);
	else
		arg_builder_add_string(chrlst, home, 0);
	free(home);
	return (1);
}
