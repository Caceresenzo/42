/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:22:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:22:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin_handler_exit(t_builtin_param param)
{
	char	code;

	if (param.argc == 1)
		minishell_exit(0);
	else
	{
		if (ft_str_isdigit(param.argv[1], 1, 1))
		{
			code = (char)ft_atoi(param.argv[1]);
			if (param.argc > 2)
				builtin_error(g_shell, param, NULL, ERR_TOO_MANY_ARGS);
			else
				minishell_exit(code);
		}
		else
		{
			builtin_error(g_shell, param, param.argv[1], ERR_NUM_ARG_REQ);
			minishell_exit(255);
		}
	}
}
