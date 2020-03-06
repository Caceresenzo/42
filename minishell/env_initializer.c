/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_initializer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:55:58 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 17:55:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arrlst	g_env_variables;

void
	env_initialize(char **envp)
{
	arraylist_init(&g_env_variables, &env_compare_by_name, 10);
	if (envp != NULL)
		env_load(envp);
}
