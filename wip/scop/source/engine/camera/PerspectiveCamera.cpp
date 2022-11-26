/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PerspectiveCamera.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 22:47:13 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/27 22:47:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/camera/PerspectiveCamera.hpp>
#include <engine/control/Keyboard.hpp>
#include <engine/math/Matrix.hpp>
#include <lang/Math.hpp>
#include <cmath>
#include <iostream>

PerspectiveCamera::PerspectiveCamera(const Vector<3, float> &position, float yaw, float pitch) :
	m_position(position),
	m_front(/* will be computed*/),
	m_up(/* will be computed*/),
	m_right(/* will be computed*/),
	m_world_up(0.0f, 1.0f, 0.0f),
	m_yaw(yaw),
	m_pitch(pitch),
	m_speed(2.5f),
	m_sensitivity(0.1f),
	m_view_matrix(/* will be computed*/)
{
	compute_vectors();
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void
PerspectiveCamera::move(double delta_time)
{
	bool updated = false;
	float velocity = m_speed * delta_time;

	if (Keyboard::is_pressed(Keyboard::LEFT_SHIFT))
		velocity *= 5;

	Vector<3, float> up(0, 1, 0);
	Vector<3, float> right = ::normalize(::cross(m_front, up));
	Vector<3, float> forward(Math::cos(Math::radians(m_yaw)), 0, Math::sin(Math::radians(m_yaw)));

	if (Keyboard::is_pressed(Keyboard::W))
	{
		m_position += forward * velocity;
		updated = true;
	}

	if (Keyboard::is_pressed(Keyboard::S))
	{
		m_position -= forward * velocity;
		updated = true;
	}

	if (Keyboard::is_pressed(Keyboard::A))
	{
		m_position -= right * velocity;
		updated = true;
	}

	if (Keyboard::is_pressed(Keyboard::D))
	{
		m_position += right * velocity;
		updated = true;
	}

	if (Keyboard::is_pressed(Keyboard::I))
	{
		m_pitch += 50 * velocity;

		if (m_pitch > 89.0f)
			m_pitch = 89.0f;

		updated = true;
	}

	if (Keyboard::is_pressed(Keyboard::K))
	{
		m_pitch += -50 * velocity;

		if (m_pitch < -89.0f)
			m_pitch = -89.0f;

		updated = true;
	}

	if (Keyboard::is_pressed(Keyboard::J))
	{
		m_yaw -= 50 * velocity;
		updated = true;
	}

	if (Keyboard::is_pressed(Keyboard::L))
	{
		m_yaw += 50 * velocity;
		updated = true;
	}

	if (Keyboard::is_pressed(Keyboard::Q))
	{
		m_position -= up * velocity;
		updated = true;
	}

	if (Keyboard::is_pressed(Keyboard::SPACE))
	{
		m_position += up * velocity;
		updated = true;
	}

	if (updated)
		compute_vectors();
}

void
PerspectiveCamera::look(const Vector<2, int> &offset)
{
	float yaw = m_yaw + m_sensitivity * offset.x;
	float pitch = m_pitch + m_sensitivity * offset.y;

	orient(yaw, pitch);
}

void PerspectiveCamera::teleport(const Vector<3, float> &position)
{
	m_position = position;

	compute_vectors();
}

void PerspectiveCamera::orient(float yaw, float pitch)
{
	pitch = Math::clamp(pitch, -89.0f, 89.0f);

	if (yaw < 0)
		yaw = 360 - Math::floating_modulo(-yaw, 360.0f);

	if (yaw > 360)
		yaw = 0 + Math::floating_modulo(yaw, 360.0f);

	m_yaw = yaw;
	m_pitch = pitch;

	compute_vectors();
}

void
PerspectiveCamera::compute_vectors()
{
	Vector<3, float> front;
	front.x = Math::cos(Math::radians(m_yaw)) * Math::cos(Math::radians(m_pitch));
	front.y = Math::sin(Math::radians(m_pitch));
	front.z = Math::sin(Math::radians(m_yaw)) * Math::cos(Math::radians(m_pitch));
	m_front = ::normalize(front);
	m_right = ::normalize(::cross(m_front, m_world_up));
	m_up = ::normalize(::cross(m_right, m_front));

	m_view_matrix = ::look_at(m_position, m_position + m_front, m_up);
}
