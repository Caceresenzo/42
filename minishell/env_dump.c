/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 10:53:30 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 10:53:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	env_dump_content(void)
{
	size_t		index;
	size_t		longest;
	size_t		current;
	t_env_var	*item;

	index = 0;
	longest = 0;
	while (index < g_env_variables.size)
	{
		current = ft_strlen(((t_env_var *)g_env_variables.items[index])->name);
		if (current > longest)
			longest = current;
		index++;
	}
	index = 0;
	while (index < g_env_variables.size)
	{
		item = (t_env_var *)g_env_variables.items[index];
		ft_printf("%3d | \e[92m%*s\e[0m = \e[93m%s\e[0m\n",
					index, (int)(0 + longest), item->name, item->value);
		index++;
	}
}
