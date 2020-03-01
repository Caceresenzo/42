/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:04:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 19:04:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var
	*env_var_create_from_line(char *line)
{
	char	*equal;

	equal = ft_strchr(line, '=');
	if (equal == NULL)
		return (NULL);
	equal[0] = '\0';
	equal++;
	return (env_var_create(line, equal));
}

t_env_var
	*env_var_create(char *name, char *value)
{
	t_env_var	*var;

	if (!(var = (t_env_var *)malloc(sizeof(t_env_var))))
		return (NULL);
	var->name = ft_strdup(name);
	var->name_len = ft_strlen(name);
	var->value = ft_strdup(value);
	if (var->name == NULL || var->value == NULL)
		env_var_free_and_release(&var);
	return (var);
}
