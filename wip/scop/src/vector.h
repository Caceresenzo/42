/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 14:56:04 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 14:56:04 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_v3f
{
	float x;
	float y;
	float z;
} t_v3f;

t_v3f*
v3f_initialize(t_v3f *v3, float f);

t_v3f*
v3f_copy(t_v3f *v3, const t_v3f *template);

float
v3f_length_squared(t_v3f *v3);

t_v3f*
v3f_normalize(t_v3f *v3);

float
v3f_dot(const t_v3f *a, const t_v3f *b);

t_v3f*
v3f_cross(t_v3f *v3, const t_v3f *a, const t_v3f *b);

t_v3f*
v3f_add_v3(t_v3f *v3, const t_v3f *a, const t_v3f *b);

t_v3f*
v3f_sub_v3(t_v3f *v3, const t_v3f *a, const t_v3f *b);

t_v3f*
v3f_mul(t_v3f *v3, float f);

#endif
