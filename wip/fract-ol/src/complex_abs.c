#include "complex.h"

t_complex_part
complex_abs_no_sqrt(t_complex *complex)
{
	return ((complex->real * complex->real) + (complex->imag * complex->imag));
}
