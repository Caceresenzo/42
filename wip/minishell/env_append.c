/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:29:53 by ecaceres          #+#    #+#             */
/*   Updated: 2020/03/01 18:29:53 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var
	*env_append_from_line(char *line)
{
	char		*modified;
	char		*eq;
	t_env_var	*var;

	modified = ft_strdup(line);
	eq = ft_strchr(modified, '=');
	if (eq == NULL || eq == line || eq - 1 == line)
	{
		free(modified);
		return (NULL);
	}
	eq[0] = '\0';
	eq[-1] = '\0';
	var = env_get_by_name(modified);
	if (var == NULL)
	{
		var = env_var_create(modified, eq + 1);
		env_set(var);
	}
	else
		env_append(var, eq + 1);
	free(modified);
	return (var);
}

void
	env_append(t_env_var *var, char *str)
{
	if (var->value == NULL)
		var->value = ft_strdup(str);
	else
		var->value = ft_strjoin_free(var->value, str, FT_STRJOIN_FREE_FIRST);
	if (ft_strcmp(var->name, "HOME") == 0)
		home_set_cache(var->value);
}
