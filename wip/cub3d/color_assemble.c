/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_assemble.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:04:19 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/26 12:04:19 by ecaceres         ###   ########.fr       */
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
