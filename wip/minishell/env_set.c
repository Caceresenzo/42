/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:04:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 19:04:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	env_set_from_line(char *line)
{
	t_env_var	*var;

	var = env_var_create_from_line(line);
	if (var == NULL)
		return (0);
	env_set(var);
	return (1);
}

void
	env_set(t_env_var *var)
{
	if (var == NULL)
		return ;
	env_unset_from_name(var->name);
	arraylist_add(&g_env_variables, var);
	env_array_invalidate();
}
