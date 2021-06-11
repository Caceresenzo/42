/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 22:55:59 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/10 22:55:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int
	usage(const char *argv0)
{
	ft_write(STDERR, "usage: ");
	ft_write(STDERR, argv0);
	ft_write(STDERR, " file1 cmd1 cmd2 ... cmdn file2\n");
	return (1);
}

int
	main(int argc, const char **argv, const char **envp)
{
	env_init(envp);
	if (argc < 5)
		return (usage(argv[0]));
	return (pipex((t_pipex_params){
			.in = argv[1],
			.out = argv[argc - 1],
			.programs = argv + 2,
			.program_count = argc - 2 - 1
		}));
}
