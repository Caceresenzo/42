/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_dismentle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:04:44 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/26 12:04:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	color_dismentle(int color, int *red, int *green, int *blue)
{
	*red = (color >> 16) & 0xFF;
	*green = (color >> 8) & 0xFF;
	*blue = color & 0xFF;
}
