/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:29:04 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:29:04 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include <stdbool.h>

typedef struct
{
	int x;
	int y;
} t_vector2i;

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define CLAMP(x,lo,hi) MIN((hi), MAX((lo), (x)))

t_vector2i
vector2i(int x, int y);

t_vector2i
vector2i_zero(void);

bool
vector2i_equals(t_vector2i left, t_vector2i right);

t_vector2i
vector2i_substract(t_vector2i left, t_vector2i right);

t_vector2i
vector2i_add(t_vector2i left, t_vector2i right);

t_vector2i
vector2i_max(t_vector2i left, t_vector2i right);

#endif
