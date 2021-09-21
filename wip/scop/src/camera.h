/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:05:24 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 15:05:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"
# include "matrix.h"

typedef struct s_camera
{
	t_v3f position;
	t_v3f front;
	t_v3f up;
	t_v3f right;
	t_v3f world_up;
	float yaw;
	float pitch;
	float speed;
} t_camera;

void
camera_initialize(t_camera *camera);

void
camera_update(t_camera *camera);

t_m4f*
camera_look_at(const t_camera *camera, t_m4f *m4);

#endif
