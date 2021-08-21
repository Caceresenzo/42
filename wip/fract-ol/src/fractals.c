#include <stdio.h>
#include <string.h>

#include "fractol.h"

t_fractal*
fractal_list()
{
	static t_fractal fractals[] = {
		{
			.name = "mandelbrot",
			.init = &fractal_mandelbrot_init,
			.step = &fractal_mandelbrot_step },
		{
			.name = "julia",
			.init = &fractal_julia_init,
			.step = &fractal_julia_step },
		{
			.name = NULL,
			.init = NULL,
			.step = NULL }, };

	return (fractals);
}

t_fractal*
fractal_find(const char *name)
{
	t_fractal *fractal;

	fractal = fractal_list();
	while (fractal->name && strcmp(fractal->name, name) != 0)
		fractal++;
	if (fractal->name)
		return (fractal);
	return (NULL);
}
