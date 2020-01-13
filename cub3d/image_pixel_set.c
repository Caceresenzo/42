/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_pixel_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 14:38:17 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/24 14:38:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void
	image_pixel_set(t_image *image, int x, int y, int color)
{
	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	image->pic[(y * image->line_unit) + x] = color;
}
