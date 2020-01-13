/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:45:58 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 14:45:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

typedef struct		s_vec2d
{
	double			x;
	double			y;
}					t_vec2d;

typedef struct		s_vec2i
{
	int				x;
	int				y;
}					t_vec2i;

typedef struct		s_dim2i
{
	int				w;
	int				h;
}					t_dim2i;

void				vector2i_add(t_vec2i *dest, t_vec2i a, t_vec2i b);

#endif
