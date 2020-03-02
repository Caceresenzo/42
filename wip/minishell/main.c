/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:18:34 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:18:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	main(int argc, char **argv, char **envp)
{
	t_mshell	shell;

	ft_fake_use(&argc);
	ft_fake_use(&argv);
	minishell_signals_attach();
	env_initialize(envp);
	minishell_initialize(&shell, argv[0]);
	minishell_pre_loop();
	minishell_input_loop(&shell);
	minishell_exit(0);
	return (EXIT_SUCCESS);
}
