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
#include <engine/math/matrix.hpp>
#include <engine/math/Math.hpp>
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
		m_zoom(45.0f),
		m_view_matrix(/* will be computed*/)
{
	compute_vectors();
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void
PerspectiveCamera::move(double delta)
{
	bool updated = false;
	float velocity = m_speed * delta;

	if (Keyboard::is_pressed(Keyboard::Z))
	{
		m_position += m_front * velocity;
		updated = true;
	}

	if (Keyboard::is_pressed(Keyboard::S))
	{
		m_position -= m_front * velocity;
		updated = true;
	}

	if (Keyboard::is_pressed(Keyboard::Q))
	{
		m_position -= m_right * velocity;
		updated = true;
	}

	if (Keyboard::is_pressed(Keyboard::D))
	{
		m_position += m_right * velocity;
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

	if (Keyboard::is_pressed(Keyboard::A))
	{
		m_position -= m_up * velocity;
		updated = true;
	}

	if (Keyboard::is_pressed(Keyboard::SPACE))
	{
		m_position += m_up * velocity;
		updated = true;
	}

	if (updated)
		compute_vectors();
}

void
PerspectiveCamera::look(const Vector<2, int> &offset)
{
	m_yaw += m_sensitivity * offset.x;
	m_pitch += m_sensitivity * offset.y;

	m_pitch = Math::clamp(m_pitch, -89.0f, 89.0f);

	compute_vectors();
}

const Vector<3, float>&
PerspectiveCamera::position() const
{
	return (m_position);
}

const Matrix<4, 4, float>&
PerspectiveCamera::view_matrix() const
{
	return (m_view_matrix);
}

float
PerspectiveCamera::yaw() const
{
	return (m_yaw);
}

float
PerspectiveCamera::pitch() const
{
	return (m_pitch);
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
