#include "complex.h"
#include "fractol.h"

int
fractal_run(t_fractol *fractol, t_complex *at)
{
	int iteration;
	t_complex complex;

	iteration = 0;
	complex = *at;
	while (iteration < fractol->max_iteration)
	{
		if (complex_abs_no_sqrt(&complex) > 4)
			return (hsv2rgb((double)iteration / 255.0 * 100, 100, 50));
		(*fractol->fractal->step)(&complex, &fractol->first, at);
		iteration++;
	}
	return (0);
}
