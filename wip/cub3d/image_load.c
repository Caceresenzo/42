/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:42:12 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 16:42:12 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

t_image
	*image_load(void *mlx_ptr, char *path)
{
	t_image *img;

	if (!(img = malloc(sizeof(t_image))))
		return (NULL);
	if (!(img->ptr = mlx_png_file_to_image(mlx_ptr, path, &img->width,
											&img->height))
		|| !(img->pic = (int *)mlx_get_data_addr(img->ptr, &img->bpp,
												&img->stride, &img->endian)))
		return (NULL);
	img->line_unit = img->stride / sizeof(int);
	img->bpp /= 8;
	return (img);
}
