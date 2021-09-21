/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_perspective.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:55:01 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 16:55:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "matrix.h"

/* from https://stackoverflow.com/a/10758985 */

void
m4f_perspective(t_m4f *m4, float fov, float aspect, float zNear, float zFar)
{
	const float tanHalfFovy = tan(fov / 2.0f);

	m4f_zero(m4);
	m4->m[0][0] = (1.0f) / (aspect * tanHalfFovy);
	m4->m[1][1] = (1.0f) / (tanHalfFovy);
	m4->m[2][2] = -(zFar + zNear) / (zFar - zNear);
	m4->m[2][3] = -(1.0f);
	m4->m[3][2] = -((2.0f) * zFar * zNear) / (zFar - zNear);
}
