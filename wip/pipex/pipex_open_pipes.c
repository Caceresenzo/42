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

bool
	pipex_open_pipes(t_pipex_internal *internal)
{
	int			index;

	index = 0;
	while (index < internal->params->program_count - 1)
	{
		if (pipe(internal->pipes[index]) == -1)
			return (false);
		index++;
	}
	return (true);
}
