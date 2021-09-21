/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_process_keyboard.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:46:49 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/21 14:46:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "keyboard.h"

void
camera_process_keyboard(t_camera *camera, float delta)
{
	bool updated = false;
	float velocity = camera->speed * delta;

	if (keyboard_key_get(KEY_Z) || keyboard_key_get(KEY_W))
	{
		t_v3f front;
		v3f_copy(&front, &camera->front);
		v3f_mul(&front, velocity);
		v3f_add_v3(&camera->position, &camera->position, &front);

		updated = true;
	}

	if (keyboard_key_get(KEY_S))
	{
		t_v3f front;
		v3f_copy(&front, &camera->front);
		v3f_mul(&front, velocity);
		v3f_sub_v3(&camera->position, &camera->position, &front);

		updated = true;
	}

	if (keyboard_key_get(KEY_D))
	{
		t_v3f right;
		v3f_copy(&right, &camera->right);
		v3f_mul(&right, velocity);
		v3f_add_v3(&camera->position, &camera->position, &right);

		updated = true;
	}

	if (keyboard_key_get(KEY_Q) || keyboard_key_get(KEY_A))
	{
		t_v3f right;
		v3f_copy(&right, &camera->right);
		v3f_mul(&right, velocity);
		v3f_sub_v3(&camera->position, &camera->position, &right);

		updated = true;
	}

	if (keyboard_key_get(KEY_SPACE))
	{
		t_v3f up;
		v3f_copy(&up, &camera->up);
		v3f_mul(&up, velocity);
		v3f_add_v3(&camera->position, &camera->position, &up);

		updated = true;
	}

	if (keyboard_key_get(KEY_SHIFT))
	{
		t_v3f up;
		v3f_copy(&up, &camera->up);
		v3f_mul(&up, velocity);
		v3f_sub_v3(&camera->position, &camera->position, &up);

		updated = true;
	}

	if (keyboard_key_get(KEY_ARROW_LEFT))
	{
		camera->yaw -= 50 * velocity;

		updated = true;
	}

	if (keyboard_key_get(KEY_ARROW_RIGHT))
	{
		camera->yaw += 50 * velocity;

		updated = true;
	}

	if (keyboard_key_get(KEY_ARROW_UP))
	{
		camera->pitch += 50 * velocity;

		if (camera->pitch > 89.0f)
			camera->pitch = 89.0f;

		updated = true;
	}

	if (keyboard_key_get(KEY_ARROW_DOWN))
	{
		camera->pitch -= 50 * velocity;

		if (camera->pitch < -89.0f)
			camera->pitch = -89.0f;

		updated = true;
	}

	if (updated)
		camera_update(camera);
}
