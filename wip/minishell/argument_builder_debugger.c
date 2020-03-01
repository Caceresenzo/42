/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_builder_debugger.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:57:35 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 12:57:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_argument_builder_debug = 0;

void
	argument_builder_debug(int state)
{
	g_argument_builder_debug = state;
}

void
	argument_builder_debug_print_char(char chr, char quote)
{
	int	color;

	if (!g_argument_builder_debug)
		return ;
	if (quote == '\'')
		color = 92;
	else if (quote == '\"')
		color = 93;
	else
		color = 94;
	ft_printf("\e[%dm%c\e[0m", color, chr);
}

void
	argument_builder_debug_new(void)
{
	if (!g_argument_builder_debug)
		return ;
	ft_printf("\n");
}
