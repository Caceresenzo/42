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

void
	*(*image_get_mlx_loader(char *path))(void *, char *, int *, int *)
{
	char	*extension;

	extension = ft_strrchr(path, '.');
	if (extension == NULL)
		return (&mlx_png_file_to_image);
	if (ft_strcmp(extension, XPM_EXTENSION) == 0)
		return (&mlx_xpm_file_to_image);
	return (&mlx_png_file_to_image);
}

t_image
	*image_load(void *mlx_ptr, char *path)
{
	t_image *img;
	void	*(*loader)(void *, char *, int *, int *);

	if (!path || !(img = malloc(sizeof(t_image))))
		return (NULL);
	loader = image_get_mlx_loader(path);
	if (!(img->ptr = (*loader)(mlx_ptr, path, &img->width, &img->height))
		|| !(img->pic = (int *)mlx_get_data_addr(img->ptr, &img->bpp,
												&img->stride, &img->endian)))
		return (NULL);
	img->line_unit = img->stride / sizeof(int);
	img->bpp /= 8;
	return (img);
}
