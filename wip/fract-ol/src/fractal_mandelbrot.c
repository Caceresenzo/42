#include "fractol.h"

/**
** p0 = z
** pn+1 = pn^2 + z
*/
void
fractal_mandelbrot_init(t_complex *z0)
{
	z0->real = 0;
	z0->imag = 0;
}

void
fractal_mandelbrot_step(t_complex *z, t_complex *c, t_complex *set)
{
	(void)c;
	complex_multiply(z, z);
	complex_add(z, set);
}
