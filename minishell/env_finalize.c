/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_finalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:04:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 19:04:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	env_finalize(void)
{
	size_t		index;

	index = 0;
	while (index < g_env_variables.size)
	{
		env_var_free_and_release((t_env_var **)&(g_env_variables.items[index]));
		index++;
	}
	arraylist_destroy_items(&g_env_variables);
}
