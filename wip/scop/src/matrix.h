/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 14:54:24 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 14:54:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

typedef struct s_m4f
{
	float m[4][4];
} t_m4f;

void
m4f_zero(t_m4f *m4);

void
m4f_initialize(t_m4f *m4, float value);

void
m4f_identity(t_m4f *m4);

void
m4f_perspective(t_m4f *m4, float fov, float aspect, float near, float far);

t_m4f*
m4f_look_at(t_m4f *m4, const t_v3f *eye, const t_v3f *center, const t_v3f *up);

t_m4f*
m4f_translate_v3(t_m4f *m4, const t_v3f *v3);

t_m4f*
m4f_rotate_v3(t_m4f *m4, float angle, const t_v3f *v3);

t_m4f*
m4f_mul_4f(t_m4f *m4, t_m4f *a, t_m4f *b);

void
m4f_print(const t_m4f *m4);

#endif
