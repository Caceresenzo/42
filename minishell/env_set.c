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

t_env_var
	*env_set_from_line(char *line, int replace)
{
	t_env_var	*var;
	t_env_var	*previous;

	var = env_var_create_from_line(line);
	if (var == NULL)
		return (NULL);
	if (!replace && ((previous = env_get_by_name(var->name)) != NULL)
		&& previous->value != NULL)
	{
		env_var_free_and_release(&var);
		return (NULL);
	}
	env_set(var);
	return (var);
}

void
	env_set(t_env_var *var)
{
	if (var == NULL)
		return ;
	env_unset_from_name(var->name);
	arraylist_add(&g_env_variables, var);
	env_array_invalidate();
	if (ft_strcmp(var->name, "HOME") == 0)
		home_set_cache(var->value);
}
