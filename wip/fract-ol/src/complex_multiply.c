#include "complex.h"

void
complex_multiply(t_complex *complex, t_complex *right)
{
	t_complex_part real;
	t_complex_part imag;

	real = complex->real * right->real - complex->imag * right->imag;
	imag = complex->real * right->imag + complex->imag * right->real;
	complex->real = real;
	complex->imag = imag;
}
