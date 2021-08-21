#include <mlx.h>

#include "image.h"

int
image_initialize(t_image *image)
{
	int bits_per_pixel;
	int size_line;
	int endian;
	char *data;

	data = mlx_get_data_addr(image->ptr, &bits_per_pixel, &size_line, &endian);
	if (!data)
		return (0);
	image->pic = (int*)data;
	image->size_line = size_line / (bits_per_pixel / 8);
	return (1);
}
