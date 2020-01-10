/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_side_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:32:01 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/10 14:32:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char
	*map_side_to_str(int side)
{
	if (side < 0 || side > 3)
		return ("INVALID");
	return (((char *[4]){
		"NORTH",
		"SOUTH",
		"WEST",
		"EAST"
	})[side]);
}
