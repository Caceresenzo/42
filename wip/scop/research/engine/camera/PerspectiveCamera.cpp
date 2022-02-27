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
#include <engine/math/matrix.hpp>
#include <engine/math/Math.hpp>
#include <cmath>

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

const Matrix<4, 4, float>&
PerspectiveCamera::get_view_matrix() const
{
	return (m_view_matrix);
}

void
PerspectiveCamera::move(double delta)
{
	m_yaw += 0.8;
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
