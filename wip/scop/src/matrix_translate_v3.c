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

#include "matrix.h"

t_m4f*
m4f_translate_v3(t_m4f *m4, const t_v3f *v3)
{
	m4->m[3][0] += m4->m[0][0] * v3->x + m4->m[1][0] * v3->y + m4->m[2][0] * v3->z;
	m4->m[3][1] += m4->m[0][1] * v3->x + m4->m[1][1] * v3->y + m4->m[2][1] * v3->z;
	m4->m[3][2] += m4->m[0][2] * v3->x + m4->m[1][2] * v3->y + m4->m[2][2] * v3->z;
	m4->m[3][3] += m4->m[0][3] * v3->x + m4->m[1][3] * v3->y + m4->m[2][3] * v3->z;

	return (m4);
}
