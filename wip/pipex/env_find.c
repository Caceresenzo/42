/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 00:40:39 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/11 00:40:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

const char
	*env_find(const char *key)
{
	const char	**envp;
	const char	*entry;
	const char	*equal;

	envp = env_get();
	while (*envp)
	{
		entry = *envp;
		equal = ft_strchr(entry, '=');
		if (equal && ft_strncmp(key, entry, equal - entry) == 0)
			return (equal + 1);
		envp++;
	}
	return (NULL);
}
