/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_initialize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:46:13 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 17:46:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void
camera_initialize(t_camera *camera)
{
	camera->position = (t_v3f ) { 0.0f, 0.0f, 3.0f };
	camera->front = (t_v3f ) { 0.0f, 0.0f, -1.0f };
	camera->up = (t_v3f ) { 0.0f, 1.0f, 0.0f };
	camera->right = (t_v3f ) { 0.0f, 0.0f, 0.0f };
	camera->world_up = (t_v3f ) { 0.0f, 1.0f, 0.0f };
	camera->yaw = -90;
	camera->pitch = 1.0f;
	camera->speed = 2.5f;

	camera_update(camera);
}
