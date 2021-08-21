#include "image.h"

void
image_draw_square(t_image *image, int x, int y, int size, int color)
{
	int i;
	int j;
	int *pic;
	int size_line;

	if (x < 0 || y < 0 || x + size > image->width || y + size > image->height)
		return;

	pic = image->pic;
	size_line = image->size_line;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if ((x + i) < image->width && (y + i) < image->height)
				pic[(y + i) * size_line + (x + j)] = color;
			j++;
		}
		i++;
	}
}
