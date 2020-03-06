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

static void
	builtin_handler_export_print_value(t_builtin_param param, t_env_var *var)
{
	size_t	index;
	char	current;

	index = 0;
	while ((current = var->value[index]))
	{
		if (current == Q_DOUBLE || current == '\\')
			ft_putchar_fd('\\', param.fd_out);
		ft_putchar_fd(current, param.fd_out);
		index++;
	}
}

static void
	builtin_handler_export_print(t_builtin_param param)
{
	size_t		index;
	t_env_var	*var;
	t_arrlst	*varlst;

	if (!(varlst = arraylist_duplicate(&g_env_variables)))
		varlst = &g_env_variables;
	else
		arraylist_sort(varlst, &env_compare_name);
	index = 0;
	while (index < varlst->size)
	{
		var = (t_env_var *)varlst->items[index];
		ft_dprintf(param.fd_out, "declare -x %s", var->name);
		if (var->value != NULL)
		{
			ft_putchar_fd('=', param.fd_out);
			ft_putchar_fd('"', param.fd_out);
			builtin_handler_export_print_value(param, var);
			ft_putchar_fd('"', param.fd_out);
		}
		ft_putchar_fd('\n', param.fd_out);
		index++;
	}
	if (varlst != &g_env_variables)
		arraylist_destroy(varlst);
}

static void
	builtin_handler_export_print_handle(char *line)
{
	char		*plus;
	char		*equal;

	plus = ft_strchr(line, '+');
	equal = ft_strchr(line, '=');
	if (equal != NULL && plus != NULL && plus + 1 == equal)
		env_append_from_line(line);
	else
		env_set_from_line(line, equal != NULL);
}

void
	builtin_handler_export(t_builtin_param param)
{
	int		index;
	char	*line;

	if (param.argc == 1)
		builtin_handler_export_print(param);
	else
	{
		index = 1;
		while (index < param.argc)
		{
			line = param.argv[index];
			if (!env_var_is_name_valid(line, 1))
				builtin_error(g_shell, param, line, ERR_NOT_VALID_ID);
			else
				builtin_handler_export_print_handle(line);
			index++;
		}
	}
}
