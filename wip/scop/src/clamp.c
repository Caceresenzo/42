/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:43:39 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 16:43:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

double
clampf(float value, float min, float max)
{
	const float f = value < min ? min : value;
	return (f > max ? max : f);
}
