/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_normalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:45:17 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 15:45:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "vector.h"

t_v3f*
v3f_normalize(t_v3f *v3)
{
	float length_square = v3f_length_squared(v3);

	if (length_square == 0)
	{
		v3->x = 0;
		v3->y = 0;
		v3->z = 0;
	}
	else
	{
		float length = sqrtf(length_square);
		v3->x /= length;
		v3->y /= length;
		v3->z /= length;
	}

	return (v3);
}
