/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_look_at.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:17:01 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 17:17:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

t_m4f*
camera_look_at(const t_camera *camera, t_m4f *m4)
{
	m4->m[0][0] = camera->right.x;
	m4->m[0][1] = camera->right.y;
	m4->m[0][2] = camera->right.z;
	m4->m[0][3] = 0.0f;
	m4->m[1][0] = camera->up.x;
	m4->m[1][1] = camera->up.y;
	m4->m[1][2] = camera->up.z;
	m4->m[1][3] = 0.0f;
	m4->m[2][0] = camera->front.x;
	m4->m[2][1] = camera->front.y;
	m4->m[2][2] = camera->front.z;
	m4->m[1][3] = 0.0f;
	m4->m[3][0] = camera->position.x;
	m4->m[3][1] = camera->position.y;
	m4->m[3][2] = camera->position.z;
	m4->m[3][0] = 0.0f;

	return (m4);
}
