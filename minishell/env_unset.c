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

void
	env_unset_from_name(char *name)
{
	if (name == NULL)
		return ;
	arraylist_remove(&g_env_variables, name, &env_var_free);
	env_array_invalidate();
}
