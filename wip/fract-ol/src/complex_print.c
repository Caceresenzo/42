#include <stdio.h>

#include "complex.h"

void
complex_print(t_complex *this)
{
	printf("Complex[real=%lf, imag=%lf]\n", this->real, this->imag);
}
