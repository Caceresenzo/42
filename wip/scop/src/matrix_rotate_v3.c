/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_translate_v3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:06:30 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 18:06:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "matrix.h"

t_m4f*
m4f_rotate_v3(t_m4f *m4, float angle, const t_v3f *v3)
{
	const float a = angle;
	const float c = cos(a);
	const float s = sin(a);

	t_v3f axis = *v3;
	v3f_normalize(&axis);

	t_m4f result;

	result.m[0][0] = c + ((1.0f) - c) * axis.x * axis.x;
	result.m[0][1] = ((1.0f) - c) * axis.x * axis.y + s * axis.z;
	result.m[0][2] = ((1.0f) - c) * axis.x * axis.z - s * axis.y;
	result.m[0][3] = (0.0f);

	result.m[1][0] = ((1.0f) - c) * axis.y * axis.x - s * axis.z;
	result.m[1][1] = c + ((1.0f) - c) * axis.y * axis.y;
	result.m[1][2] = ((1.0f) - c) * axis.y * axis.z + s * axis.x;
	result.m[1][3] = (0.0f);

	result.m[2][0] = ((1.0f) - c) * axis.z * axis.x + s * axis.y;
	result.m[2][1] = ((1.0f) - c) * axis.z * axis.y - s * axis.x;
	result.m[2][2] = c + ((1.0f) - c) * axis.z * axis.z;
	result.m[2][3] = (0.0f);

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	t_m4f b = *m4;

	return (m4f_mul_4f(m4, &b, &result));
}
