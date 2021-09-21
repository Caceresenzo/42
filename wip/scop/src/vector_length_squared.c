/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_length_squared.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:42:40 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 15:42:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float
v3f_length_squared(t_v3f *v3)
{
	float x = v3->x;
	float y = v3->y;
	float z = v3->z;

	return ((x * x) + (y * y) + (z * z));
}
