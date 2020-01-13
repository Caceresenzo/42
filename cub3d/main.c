/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:04:50 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/12 15:04:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	find_save_arg(int argc, char **argv)
{
	int		index;
	int		unsupported;
	int		save_found;
	char	*arg;

	index = 2;
	unsupported = 0;
	save_found = 0;
	while (index < argc)
	{
		arg = argv[index];
		if (ft_strchr(arg, '-') == arg)
		{
			if ((save_found = ft_strcmp(arg, "-save") == 0))
				break ;
			engine_error(ft_strjoin("Unsupported argument: ", arg));
		}
		else
			unsupported = index;
		index++;
	}
	if (save_found && unsupported)
		engine_error(ft_strjoin("Unsupported input: ", argv[unsupported]));
	return (save_found);
}

int
	main(int argc, char **argv)
{
	int		save_arg;

	errno = 0;
	if (argc == 1)
	{
		ft_putendl_fd(CUB3D_USAGE, ERR);
		return (1);
	}
	save_arg = 0;
	if (argc >= 3)
		save_arg = find_save_arg(argc, argv);
	if (argc < 2)
	{
		engine_error(e("No file specified"));
		return (1);
	}
	return (engine_initialize(argv[1], save_arg));
}
