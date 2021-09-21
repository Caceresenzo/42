/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cross.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:35:01 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 16:35:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>

#include "vector.h"

t_v3f*
v3f_cross(t_v3f *v3, const t_v3f *a, const t_v3f *b)
{
	assert(v3 != a);
	assert(v3 != b);

	v3->x = (a->y * b->z) - (a->z * b->y);
	v3->y = (a->z * b->x) - (a->x * b->z);
	v3->z = (a->x * b->y) - (a->y * b->x);

	return (v3);
}
