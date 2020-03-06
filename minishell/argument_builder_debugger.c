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

int		g_arg_builder_debug = 0;

void
	arg_builder_debug(int state)
{
	g_arg_builder_debug = state;
}

void
	arg_builder_debug_print_char(char chr, char quote)
{
	int	color;

	if (!g_arg_builder_debug)
		return ;
	if (quote == Q_SINGLE)
		color = 92;
	else if (quote == Q_DOUBLE)
		color = 93;
	else
		color = 94;
	ft_printf("\e[%dm%c\e[0m", color, chr);
}

void
	arg_builder_debug_new(void)
{
	if (!g_arg_builder_debug)
		return ;
	ft_printf("\n");
}
