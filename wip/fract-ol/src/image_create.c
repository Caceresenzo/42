#include <mlx.h>
#include <stdio.h>

#include "image.h"

void*
image_create(void *mlx, t_image *image, int width, int height)
{
	void *img;

	img = mlx_new_image(mlx, width, height);
	if (!img)
		return (0);
	image->ptr = img;
	image->width = width;
	image->height = height;
	if (!image_initialize(image))
	{
		image_destroy(mlx, image);
		return (0);
	}
	return (img);
}
