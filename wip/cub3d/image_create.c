/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:44:49 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 10:44:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

t_image
	*image_create(void *mlx_ptr, int width, int height)
{
	t_image *img;

	if (!(img = malloc(sizeof(t_image))))
		return (NULL);
	if (!(img->ptr = mlx_new_image(mlx_ptr, width, height))
		|| !(img->pic = (int *)mlx_get_data_addr(img->ptr, &img->bpp,
												&img->stride, &img->endian)))
		return (NULL);
	img->width = width;
	img->height = height;
	img->line_unit = img->stride / sizeof(int);
	img->bpp /= 8;
	return (img);
}
