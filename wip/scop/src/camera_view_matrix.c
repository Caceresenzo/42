/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_view_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:17:01 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 17:17:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_m4f*
camera_view_matrix(const t_camera *camera, t_m4f *m4)
{
	t_v3f center;
	v3f_copy(&center, &camera->position);
	v3f_add_v3(&center, &camera->position, &camera->front);

	m4f_look_at(m4, &camera->position, &center, &camera->up);

	return (m4);
}
