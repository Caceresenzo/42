#ifndef IMAGE_H
#define IMAGE_H

typedef struct s_image
{
	void *ptr;
	int *pic;
	int width;
	int height;
	int size_line;
} t_image;

void*
image_create(void *mlx, t_image *image, int width, int height);

int
image_initialize(t_image *image);

void
image_destroy(void *mlx, t_image *image);

void
image_draw_square(t_image *image, int x, int y, int size, int color);

#endif
