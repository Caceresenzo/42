/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:02:20 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 19:02:20 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	env_load(char **envp)
{
	size_t	index;
	char	*line;

	index = 0;
	while ((line = envp[index]) != NULL)
	{
		env_set_from_line(line);
		index++;
	}
	return (1);
}
