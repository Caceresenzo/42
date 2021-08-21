#include "complex.h"
#include "fractol.h"

void
mapped_point(t_fractol *fractol, t_complex *complex, int x, int y)
{
	complex->real = ((double)x - (double)fractol->view.width * 0.5) * fractol->zoom + fractol->center.real;
	complex->imag = ((double)fractol->view.height * 0.5 - (double)y) * fractol->zoom + fractol->center.imag;
}
