/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader_set_resolution.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:43:02 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 17:43:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define INDEX_WIDTH 0
#define INDEX_HEIGHT 1

static void
	i_map_check_resolution_range(char *key, int ints[2], int index, char **ptr)
{
	int		value;

	if (*ptr != NULL)
		return ;
	value = ints[index];
	if (value > 0)
		return ;
	if (index == INDEX_WIDTH)
		*ptr = ft_strjoin("WIDTH value out of range for config key: ", key);
	else if (index == INDEX_HEIGHT)
		*ptr = ft_strjoin("HEIGHT value out of range for config key: ", key);
}

char
	*map_loader_set_resolution(char *key, char **resolutions, t_engine *eng)
{
	char	*error;
	size_t	length;
	int		ints[2];

	error = NULL;
	length = ft_split_length(resolutions);
	if (length != 2)
		return (ft_strjoin("Invalid resolution format for config key: ", key));
	if (eng->ctx.width != -1)
		return (e("Already assigned resolution"));
	ints[0] = ft_atoi(resolutions[0]);
	ints[1] = ft_atoi(resolutions[1]);
	i_map_check_resolution_range(key, ints, INDEX_WIDTH, &error);
	i_map_check_resolution_range(key, ints, INDEX_HEIGHT, &error);
	if (error == NULL)
	{
		eng->ctx.width = ints[INDEX_WIDTH];
		eng->ctx.height = ints[INDEX_HEIGHT];
	}
	return (error);
}
