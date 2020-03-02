/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_cache.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:07:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/03/01 18:07:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_home = NULL;

void
	home_set_cache(char *value)
{
	char	*dup;

	if (value == NULL || !(dup = ft_strdup(value)))
		return ;
	if (g_home != NULL)
		free(g_home);
	g_home = dup;
}

char
	*home_get_cache(void)
{
	return (ft_strdup(g_home == NULL ? "" : g_home));
}
