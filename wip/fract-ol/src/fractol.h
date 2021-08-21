#ifndef FRACTOL_H
#define FRACTOL_H

#include "complex.h"
#include "vec2.h"
#include "image.h"
#include <mlx.h>

typedef struct s_fractal
{
	char *name;
	void
	(*init)(t_complex*);
	void
	(*step)(t_complex*, t_complex*, t_complex*);
} t_fractal;

typedef struct s_fractol
{
	struct
	{
		void *ptr;
		void *win;
	} mlx;
	struct
	{
		int height;
		int width;
		t_image img;
	} view;
	t_vec2i start;
	int tile_size;
	int radius;
	t_complex center;
	t_complex first;
	int max_iteration;
	double zoom;
	struct
	{
		int start;
		int step;
	} side;
	t_fractal *fractal;
} t_fractol;

int
init(t_fractol *fractol, t_fractal *fractal);

t_fractal*
fractal_list();

t_fractal*
fractal_find(const char *name);

int
fractal_run(t_fractol *fractol, t_complex *at);

void
fractal_mandelbrot_init(t_complex *z0);

void
fractal_mandelbrot_step(t_complex *z, t_complex *c, t_complex *set);

void
fractal_julia_init(t_complex *z0);

void
fractal_julia_step(t_complex *z, t_complex *c, t_complex *set);

void
zoom_init(t_fractol *fractol);

void
zoom_recompute(t_fractol *fractol);

int
hsv2rgb(double in_h, double in_s, double in_v);

void
draw_tile(t_fractol *fractol, int x, int y, int debug);

void
draw_tiles(t_fractol *fractol, int debug);

void
mapped_point(t_fractol *fractol, t_complex *complex, int x, int y);

#endif
