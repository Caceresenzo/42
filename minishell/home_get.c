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
	*home_get_from_env(void)
{
	t_env_var	*var;

	var = env_get_by_name("HOME");
	if (var != NULL && var->name != NULL)
		return (ft_strdup(var->value));
	return (NULL);
}
