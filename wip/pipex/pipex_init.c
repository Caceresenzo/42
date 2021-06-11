/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 02:02:38 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/11 02:02:38 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool
	pipex_init(t_pipex_params *params, t_pipex_internal *internal)
{
	static int	default_pipe[2] = {-1, -1};
	int			index;

	ft_bzero(internal, sizeof(t_pipex_internal));
	internal->params = params;
	internal->in = -1;
	internal->out = -1;
	internal->pipes = ft_calloc(params->program_count - 1, sizeof(int [2]));
	internal->paths = ft_calloc(params->program_count, sizeof(char *));
	internal->pids = ft_calloc(params->program_count, sizeof(pid_t));
	if (internal->pipes)
	{
		index = 0;
		while (index < internal->params->program_count - 1)
		{
			ft_memcpy(internal->pipes[index], default_pipe, sizeof(int [2]));
			index++;
		}
	}
	return (internal->pipes && internal->paths);
}
