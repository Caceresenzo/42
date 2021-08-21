#include "complex.h"
#include "fractol.h"
#include "image.h"

void
draw_tile(t_fractol *fractol, int x, int y, int debug)
{
	int tile_x;
	int tile_y;
	int color;
	t_complex at;

	tile_x = fractol->start.x + x * fractol->tile_size;
	tile_y = fractol->start.y + y * fractol->tile_size;

	if (tile_x + fractol->tile_size / 2 < 0)
		return;
	if (tile_y + fractol->tile_size / 2 < 0)
		return;
	if (tile_x - fractol->tile_size / 2 >= fractol->view.width)
		return;
	if (tile_y - fractol->tile_size / 2 >= fractol->view.height)
		return;

	if (debug)
		color = 0xFF0000;
	else
	{
		mapped_point(fractol, &at, tile_x, tile_y);
		color = fractal_run(fractol, &at);
	}

	image_draw_square(&fractol->view.img, tile_x, tile_y, fractol->tile_size, color);
}

void
draw_tiles(t_fractol *fractol, int debug)
{
	int start;
	int step;

	start = fractol->side.start;
	step = fractol->side.step;
	draw_tile(fractol, -start + step, -start, debug);
	draw_tile(fractol, start, -start + step, debug);
	draw_tile(fractol, start - step, start, debug);
	draw_tile(fractol, -start, start - step, debug);
}
