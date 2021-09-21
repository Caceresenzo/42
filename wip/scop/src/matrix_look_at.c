/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_mul_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:31:58 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 17:31:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>

#include "matrix.h"

t_m4f*
m4f_look_at(t_m4f *m4, const t_v3f *eye, const t_v3f *center, const t_v3f *up)
{
	t_v3f f, s, u;

	v3f_normalize(v3f_sub_v3(&f, center, eye));
	v3f_normalize(v3f_cross(&s, &f, up));
	v3f_cross(&u, &s, &f);

	m4f_identity(m4);

	m4->m[0][0] = s.x;
	m4->m[1][0] = s.y;
	m4->m[2][0] = s.z;
	m4->m[0][1] = u.x;
	m4->m[1][1] = u.y;
	m4->m[2][1] = u.z;
	m4->m[0][2] = -f.x;
	m4->m[1][2] = -f.y;
	m4->m[2][2] = -f.z;
	m4->m[3][0] = -v3f_dot(&s, eye);
	m4->m[3][1] = -v3f_dot(&u, eye);
	m4->m[3][2] = v3f_dot(&f, eye);

	return (m4);
}
