/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:22:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:22:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin_handler_unset(t_builtin_param param)
{
	int		index;
	char	*line;

	index = 1;
	while (index < param.argc)
	{
		line = param.argv[index];
		if (!env_var_is_name_valid(line, 0))
			builtin_error(g_shell, param, line, ERR_NOT_VALID_ID);
		else
			env_unset_from_name(line);
		index++;
	}
}
