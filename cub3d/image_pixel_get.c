/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_pixel_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 14:59:18 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/24 14:59:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

int
	image_pixel_get(t_image *image, int x, int y)
{
	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return (-1);
	return (image->pic[(y * image->line_unit) + x]);
}
