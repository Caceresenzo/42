/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_interrupt.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:50:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 14:50:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal_interrupt = 0;

void
	signal_handler_interrupt(int sig)
{
	signal(SIGINT, SIG_IGN);
	g_signal_interrupt = 1;
	if (g_shell->last_pid != 0)
	{
		ft_printf("\n");
		minishell_process_kill(g_shell, sig);
	}
	else
	{
		minishell_prompt_clear_last(0);
		minishell_prompt_ask(g_shell, 1);
	}
	g_shell->last_code = sig;
	if (INTERRUPT_DOES_EXIT)
		exit(1);
	signal(SIGINT, &signal_handler_interrupt);
}

int
	signal_has_interrupt(int and_reset)
{
	int	value;

	value = g_signal_interrupt;
	if (and_reset)
		g_signal_interrupt = 0;
	return (value);
}
