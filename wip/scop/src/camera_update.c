/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:10:02 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 15:10:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "camera.h"
#include "trigonometric.h"
#include "math.h"

void
camera_update(t_camera *camera)
{
	camera->front.x = cosf(radiansf(camera->yaw)) * cos(radiansf(camera->pitch));
	camera->front.y = sinf(radiansf(camera->pitch));
	camera->front.z = sinf(radiansf(camera->yaw)) * cos(radiansf(camera->pitch));
	v3f_normalize(&camera->front);

//	printf("camera: %8.4f %8.4f %8.4f\n", camera->front.x, camera->front.y, camera->front.z);

	v3f_normalize(v3f_cross(&camera->right, &camera->front, &camera->world_up));
	v3f_normalize(v3f_cross(&camera->up, &camera->right, &camera->front));
}
