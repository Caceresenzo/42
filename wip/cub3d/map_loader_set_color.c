/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader_set_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:11:22 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 17:11:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define INDEX_RED 0
#define INDEX_GREEN 1
#define INDEX_BLUE 2

static void
	i_map_check_color_range(char *key, int ints[3], int index, char **ptr)
{
	int		value;

	if (*ptr != NULL)
		return ;
	value = ints[index];
	if (value < 0 || value > 255)
	{
		if (index == INDEX_RED)
			*ptr = ft_strjoin("RED value out of range for config key: ", key);
		else if (index == INDEX_GREEN)
			*ptr = ft_strjoin("GREEN value out of range for config key: ", key);
		else if (index == INDEX_BLUE)
			*ptr = ft_strjoin("BLUE value out of range for config key: ", key);
	}
}

char
	*map_loader_set_color(char *key, char *colors, int *color_ptr, char *name)
{
	char	**rgb;
	int		ints[3];
	size_t	length;
	char	*error;

	if (*color_ptr != -1)
		return (ft_strjoin("Already assigned color: ", name));
	rgb = ft_split(colors, ',');
	length = ft_split_length(rgb);
	error = NULL;
	if (length != 3)
		error = ft_strjoin("Invalid RGB color format for config key: ", key);
	else
	{
		ints[0] = ft_atoi(rgb[0]);
		ints[1] = ft_atoi(rgb[1]);
		ints[2] = ft_atoi(rgb[2]);
		ft_split_free(&rgb);
		i_map_check_color_range(key, ints, INDEX_RED, &error);
		i_map_check_color_range(key, ints, INDEX_GREEN, &error);
		i_map_check_color_range(key, ints, INDEX_BLUE, &error);
		if (error == NULL)
			*color_ptr = color_assemble(ints[0], ints[1], ints[2]);
	}
	return (error);
}
