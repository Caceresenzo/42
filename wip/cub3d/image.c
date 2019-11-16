/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:42:12 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 16:42:12 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image
	*image_create(t_engine *eng, int width, int height)
{
	t_image *img;

	CHECK_MALLOC(img, sizeof(t_image));
	CHECK_PTR(img->ptr = mlx_new_image(eng->ctx.mlx, width, height));
	CHECK_PTR(img->pic = mlx_get_data_addr(img->ptr, &img->bpp,
											&img->stride, &img->endian));
	img->bpp /= 8;
	img->width = width;
	img->height = height;
	return (img);
}

t_image
	*image_load(t_engine *eng, char *path)
{
	t_image *img;

	CHECK_MALLOC(img, sizeof(t_image));
	CHECK_PTR(img->ptr = mlx_png_file_to_image(eng->ctx.mlx, path, &img->width,
											&img->height));
	CHECK_PTR(img->pic = mlx_get_data_addr(img->ptr, &img->bpp,
											&img->stride, &img->endian));
	img->bpp /= 8;
	return (img);
}
