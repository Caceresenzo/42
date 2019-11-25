/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader_file_extension.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:23:28 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 14:23:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	map_loader_check_file_extension(char *path)
{
	char	*extension;

	extension = ft_strrchr(path, '.');
	if (extension == NULL)
		return (0);
	return (ft_strncmp(extension, CUB3D_FILE_EXTENSION,
						ft_strlen(CUB3D_FILE_EXTENSION) + 2) == 0);
}
