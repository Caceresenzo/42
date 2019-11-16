/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:48:59 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 14:48:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	color_assemble(int red, int green, int blue)
{
	int		color;

	color = red;
	color = (color << 8) + green;
	color = (color << 8) + blue;
	return (color);
}

void
	color_dismentle(int color, int *red, int *green, int *blue)
{
	*red = (color >> 16) & 0xFF;
	*green = (color >> 8) & 0xFF;
	*blue = color & 0xFF;
}
