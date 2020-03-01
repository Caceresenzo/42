/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pre_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:33:08 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:33:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	minishell_pre_loop(void)
{
	int	count;

	if (DISPLAY_LOADED_VARS)
	{
		env_dump_content();
		count = (int)(0 + g_env_variables.size);
		ft_printf("\e[92mLoaded \e[93m%d \e[92mvar%s.\e[0m\n",
					count, count > 1 ? "s" : "");
	}
}
