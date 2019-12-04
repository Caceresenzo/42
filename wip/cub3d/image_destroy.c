/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:46:47 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/22 15:46:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void
	image_destroy(void *mlx_ptr, t_image *image)
{
	if (!image)
		return ;
	mlx_destroy_image(mlx_ptr, image->ptr);
	image->bpp = 0;
	image->endian = 0;
	image->height = 0;
	image->line_unit = 0;
	image->pic = NULL;
	image->ptr = NULL;
	image->stride = 0;
	image->width = 0;
	free(image);
}

void
	image_destroy_null(void *mlx_ptr, t_image **image_ptr)
{
	if (!image_ptr)
		return ;
	image_destroy(mlx_ptr, *image_ptr);
	*image_ptr = NULL;
}
