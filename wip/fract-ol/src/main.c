#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <X11/X.h>

#include "fractol.h"
#include "image.h"

int
loop(t_fractol *fractol)
{
	int current_tile;

	current_tile = (fractol->side.start - 1) * fractol->tile_size * 2;
	if (current_tile > fractol->view.height && current_tile > fractol->view.width)
	{
		fractol->tile_size /= 2;
		if (fractol->tile_size < 3)
			fractol->tile_size = 1;
		fractol->side.start = 0;
		fractol->side.step = 0;
	}

	if (fractol->side.start == 0)
		draw_tile(fractol, 0, 0, 0);
	else
		draw_tiles(fractol, 0);

	fractol->side.step++;
	if (fractol->side.step + 1 > fractol->side.start * 2)
	{
		fractol->side.start++;
		fractol->side.step = 0;

		printf("step start: %d\n", fractol->side.start);
	}

	draw_tiles(fractol, 1);
	mlx_put_image_to_window(fractol->mlx.ptr, fractol->mlx.win, fractol->view.img.ptr, 0, 0);

	return (0);
}

int
on_window_close(t_fractol *fractol)
{
	mlx_loop_end(fractol->mlx.ptr);
	return (0);
}

int
end(t_fractol *fractol, int code)
{
	image_destroy(fractol->mlx.ptr, &fractol->view.img);
	if (fractol->mlx.win)
		mlx_destroy_window(fractol->mlx.ptr, fractol->mlx.win);
	if (fractol->mlx.ptr)
	{
		mlx_destroy_display(fractol->mlx.ptr);
		free(fractol->mlx.ptr);
	}
	return (code);
}

int
main(int argc, char **argv)
{
	t_fractol fractol;
	t_fractal *fractal;
	int code;

	fractal = fractal_find(argc > 1 ? argv[1] : "mandelbrot");
	if (!fractal)
	{
		printf("no fractal for name: %s", argv[1]);
		return (1);
	}
	bzero(&fractol, sizeof(t_fractol));
	fractol.view.width = 600;
	fractol.view.height = 600;
	fractol.start.x = fractol.view.width / 2;
	fractol.start.y = fractol.view.height / 2;
	fractol.tile_size = 128;
	fractol.max_iteration = 1000;
	fractol.center.real = -0.5;
	fractol.center.imag = 0;
	(*fractal->init)(&fractol.first);
	zoom_init(&fractol);
	code = init(&fractol, fractal);
	printf("fractal: %p\n", fractol.fractal);
	if (code == 0)
	{
		mlx_hook(fractol.mlx.win, DestroyNotify, 0, &on_window_close, &fractol);
		mlx_loop_hook(fractol.mlx.ptr, &loop, &fractol);
		mlx_do_sync(fractol.mlx.ptr);
		mlx_loop(fractol.mlx.ptr);
	}
	return (end(&fractol, code));
}
