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
vector2i_zero()
{
	t_vector2i vector;

	vector.x = 0;
	vector.y = 0;
	return (vector);
}
