/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_find_home.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:58:35 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 18:58:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*utility_find_home_dir(void)
{
	t_env_var	*var;

	var = env_get_by_name("HOME");
	if (var != NULL)
		return (ft_strdup(var->value));
	var = env_get_by_name("USER");
	if (var == NULL)
		var = env_get_by_name("LOGNAME");
	if (var != NULL)
		return (ft_strjoin(BASE_HOME_DIRECTORY, var->value));
	return (ft_strdup("~"));
}
