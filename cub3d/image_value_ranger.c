/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_value_ranger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:58:26 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/25 11:58:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void
	image_range_value_x(t_image *image, int *x)
{
	if (*x < 0)
		*x = 0;
	else if (*x >= image->width)
		*x = image->width;
}

void
	image_range_value_y(t_image *image, int *y)
{
	if (*y < 0)
		*y = 0;
	else if (*y >= image->height)
		*y = image->height;
}
