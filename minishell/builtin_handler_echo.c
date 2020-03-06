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
	builtin_handler_echo(t_builtin_param param)
{
	int	n_opt;
	int	index;

	n_opt = param.argc >= 2 && ft_strcmp("-n", param.argv[1]) == 0;
	index = 1 + n_opt;
	while (index < param.argc)
	{
		ft_putstr_fd(param.argv[index], param.fd_out);
		index++;
		if (index < param.argc)
			ft_putchar_fd(' ', param.fd_out);
	}
	if (!n_opt)
		ft_putchar_fd('\n', param.fd_out);
}
