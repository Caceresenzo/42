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

int		main(int argc, char **argv)
{
	int		save_arg;

//	if ((save_arg = (argc == 3)))
//	{
//		if (ft_strncmp(argv[2], "-save", 6) != 0)
//		{
//			engine_handle_error(ft_strjoin("Unsupported argument: ", argv[2]));
//			return (1);
//		}
//		argc--;
//	}
//	if (argc != 2)
//	{
//		engine_handle_error(ft_strdup("No file specified"));
//		return (1);
//	}
//	return (engine_initialize(argv[1], save_arg));
	return (engine_initialize("maps/test.cub", 0));
}
