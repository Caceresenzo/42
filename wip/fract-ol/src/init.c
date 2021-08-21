#include <mlx.h>
#include <stdio.h>

#include "fractol.h"
#include "image.h"

int
init(t_fractol *fractol, t_fractal *fractal)
{
	fractol->mlx.ptr = mlx_init();
	if (!fractol->mlx.ptr)
	{
		perror("mlx_init() failed");
		return (1);
	}
	fractol->mlx.win = mlx_new_window(fractol->mlx.ptr, fractol->view.height, fractol->view.width, fractal->name);
	if (!fractol->mlx.ptr)
	{
		perror("mlx_new_window() failed");
		return (1);
	}
	if (!image_create(fractol->mlx.ptr, &fractol->view.img, fractol->view.height, fractol->view.width))
	{
		perror("mlx_new_image() failed");
		return (1);
	}
	fractol->fractal = fractal;
	return (0);
}
