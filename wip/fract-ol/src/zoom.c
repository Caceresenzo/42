#include "fractol.h"

void
zoom_init(t_fractol *fractol)
{
	fractol->radius = 2;
	zoom_recompute(fractol);
}

void
zoom_recompute(t_fractol *fractol)
{
	fractol->zoom = (2.0 * (double)fractol->radius) / (double)(fractol->view.height < fractol->view.width ? fractol->view.height : fractol->view.width);
}
