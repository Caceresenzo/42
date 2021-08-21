#include "fractol.h"

/**
** zn = x + yi
** zn+1 = z^2 + c
*/
void
fractal_julia_init(t_complex *z0)
{
	z0->real = -0.7;
	z0->imag = 0.27015;
}

void
fractal_julia_step(t_complex *z, t_complex *c, t_complex *set)
{
	complex_multiply(z, z);
	complex_add(z, c);
	(void)set;
}
