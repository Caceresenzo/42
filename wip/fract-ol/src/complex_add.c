#include "complex.h"

void
complex_add(t_complex *complex, t_complex *right)
{
	complex->real += right->real;
	complex->imag += right->imag;
}
