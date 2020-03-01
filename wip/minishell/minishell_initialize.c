/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_initialize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:33:08 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:33:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	minishell_initialize(t_mshell *shell, char *name)
{
	char *exec_name;

	g_shell = shell;
	exec_name = ft_strrchr(name, '/');
	shell->name = exec_name == NULL ? name : exec_name + 1;
}
