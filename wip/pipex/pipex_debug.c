/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 01:58:28 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/11 01:58:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void
	print_paths(t_pipex_internal *internal)
{
	int	index;

	index = 0;
	while (index < internal->params->program_count)
	{
		printf("		\"%s\",\n", internal->paths[index]);
		index++;
	}
}

static void
	print_pipes(t_pipex_internal *internal)
{
	int	index;

	index = 0;
	while (index < internal->params->program_count - 1)
	{
		printf("		{ %d, %d },\n", internal->pipes[index][0],
			internal->pipes[index][1]);
		index++;
	}
}

static void
	print_pids(t_pipex_internal *internal)
{
	int	index;

	index = 0;
	while (index < internal->params->program_count)
	{
		printf("		%d,\n", internal->pids[index]);
		index++;
	}
}

void
	pipex_debug(t_pipex_internal *internal)
{
	printf("t_pipex_internal {\n");
	printf("	.in = %d\n", internal->in);
	printf("	.out = %d\n", internal->out);
	printf("	.paths = [\n");
	print_paths(internal);
	printf("	],\n");
	printf("	.pipes = [\n");
	print_pipes(internal);
	printf("	]\n");
	printf("	.pids = [\n");
	print_pids(internal);
	printf("	]\n");
	printf("}\n");
}
