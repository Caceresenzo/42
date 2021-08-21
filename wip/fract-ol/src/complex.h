#ifndef COMPLEX_H
#define COMPLEX_H

typedef double t_complex_part;
typedef struct s_complex
{
	t_complex_part real;
	t_complex_part imag;
} t_complex;

void
complex_print(t_complex *this);

void
complex_add(t_complex *complex, t_complex *right);

void
complex_multiply(t_complex *complex, t_complex *right);

t_complex_part
complex_abs_no_sqrt(t_complex *complex);

#endif
