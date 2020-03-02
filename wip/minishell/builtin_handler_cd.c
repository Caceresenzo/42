/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler_cd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:22:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:22:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin_handler_cd(t_builtin_param param)
{
	char	*path;

	if (param.argc == 1)
	{
		path = home_get_from_env();
		if (path == NULL)
		{
			builtin_error(g_shell, param, NULL, ERR_HOME_NOT_SET);
			return ;
		}
	}
	else
		path = param.argv[1];
	if (path != NULL && ft_strlen(path) != 0)
		if (chdir(path) == -1)
			builtin_errno(g_shell, param, path);
	if (param.argc == 1)
		free(path);
}
