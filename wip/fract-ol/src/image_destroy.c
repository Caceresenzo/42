#include <mlx.h>
#include <strings.h>

#include "image.h"

void
image_destroy(void *mlx, t_image *image)
{
	if (image->ptr)
		mlx_destroy_image(mlx, image->ptr);
	bzero(image, sizeof(t_image));
}
