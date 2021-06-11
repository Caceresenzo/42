/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 02:00:08 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/11 02:00:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void
	close_pipes(t_pipex_internal *internal)
{
	int	index;

	if (!internal->pipes)
		return ;
	index = 0;
	while (index < internal->params->program_count - 1)
	{
		file_close(&internal->pipes[index][0]);
		file_close(&internal->pipes[index][1]);
		index++;
	}
	free(internal->pipes);
}

static void
	free_paths(t_pipex_internal *internal)
{
	int	index;

	if (!internal->paths)
		return ;
	index = 0;
	while (index < internal->params->program_count)
	{
		free(internal->paths[index]);
		index++;
	}
	free(internal->paths);
}

int
	pipex_destroy(t_pipex_internal *internal, int ret)
{
	file_close(&internal->in);
	file_close(&internal->out);
	close_pipes(internal);
	free_paths(internal);
	free(internal->pids);
	return (ret);
}
