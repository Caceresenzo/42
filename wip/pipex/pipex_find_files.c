/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_open_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 01:55:58 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/11 01:55:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool
	not_found(const char *program)
{
	ft_write(STDERR, program);
	ft_write(STDERR, ": not found within path\n");
	return (false);
}

bool
	pipex_find_files(t_pipex_internal *internal)
{
	int			index;
	const char	*program;

	index = 0;
	while (index < internal->params->program_count)
	{
		program = internal->params->programs[index];
		internal->paths[index] = path_get(program);
		if (!internal->paths[index])
			return (not_found(program));
		index++;
	}
	return (true);
}
