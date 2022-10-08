/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 00:00:47 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/29 00:00:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

t_vector2i
vector2i(int x, int y)
{
	t_vector2i vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_vector2i
vector2i_zero(void)
{
	t_vector2i vector;

	vector.x = 0;
	vector.y = 0;
	return (vector);
}

bool
vector2i_equals(t_vector2i left, t_vector2i right)
{
	return (left.x == right.x && left.y == right.y);
}

t_vector2i
vector2i_substract(t_vector2i left, t_vector2i right)
{
	t_vector2i vector;

	vector.x = left.x - right.x;
	vector.y = left.y - right.y;
	return (vector);
}

t_vector2i
vector2i_add(t_vector2i left, t_vector2i right)
{
	t_vector2i vector;

	vector.x = left.x + right.x;
	vector.y = left.y + right.y;
	return (vector);
}
