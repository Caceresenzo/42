/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_quit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:01:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 15:01:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal_quit = 0;

void
	signal_handler_quit(int sig)
{
	signal(SIGQUIT, SIG_IGN);
	g_signal_quit = 1;
	if (g_shell->last_pid != 0)
	{
		ft_printf("Quit: %d\n", sig);
		minishell_process_kill(g_shell, sig);
	}
	else
		minishell_prompt_clear_last(0);
	signal(SIGQUIT, &signal_handler_quit);
}

int
	signal_has_quit(int and_reset)
{
	int	value;

	value = g_signal_quit;
	if (and_reset)
		g_signal_quit = 0;
	return (value);
}
