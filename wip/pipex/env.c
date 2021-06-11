/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 23:03:44 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/10 23:03:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static const char	**g_envp = NULL;

void
	env_init(const char **envp)
{
	g_envp = envp;
}

const char
	**env_get(void)
{
	return (g_envp);
}
