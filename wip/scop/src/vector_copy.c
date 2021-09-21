/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:54:31 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/21 14:54:31 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_v3f*
v3f_copy(t_v3f *v3, const t_v3f *template)
{
	v3->x = template->x;
	v3->y = template->y;
	v3->z = template->z;

	return (v3);
}
