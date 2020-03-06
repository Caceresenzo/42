/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_process_kill.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:04:07 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/21 19:04:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	minishell_process_kill(t_mshell *shell, int sig)
{
	if (shell->last_pid != 0)
		kill(shell->last_pid, sig);
	shell->last_pid = 0;
}
