/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PerspectiveCamera.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 22:47:13 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/27 22:47:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERSPECTIVECAMERA_HPP_
# define PERSPECTIVECAMERA_HPP_

#include <engine/math/Matrix.hpp>
#include <engine/math/Vector.hpp>

class PerspectiveCamera
{
	private:
		Vector<3, float> m_position;
		Vector<3, float> m_front;
		Vector<3, float> m_up;
		Vector<3, float> m_right;
		Vector<3, float> m_world_up;
		float m_yaw;
		float m_pitch;
		float m_speed;
		float m_sensitivity;
		Matrix<4, 4, float> m_view_matrix;

	public:
		PerspectiveCamera(const Vector<3, float> &position = Vector<3, float>(), float yaw = -90.0f, float pitch = 0.0f);

		virtual
		~PerspectiveCamera();

	public:
		void
		move(double delta_time);

		void
		look(const Vector<2, int> &offset);

		void
		teleport(const Vector<3, float> &position);

		void
		orient(float yaw, float pitch);

		inline const Vector<3, float>&
		position() const
		{
			return (m_position);
		}

		inline float
		yaw() const
		{
			return (m_yaw);
		}

		inline float
		pitch() const
		{
			return (m_pitch);
		}

		inline float
		speed() const
		{
			return (m_speed);
		}

		inline void
		set_speed(float value)
		{
			m_speed = value;
		}

		inline const Matrix<4, 4, float>&
		view_matrix() const
		{
			return (m_view_matrix);
		}

		inline const Vector<3, float>&
		front() const
		{
			return (m_front);
		}

	protected:
		void
		compute_vectors();
};

#endif /* PERSPECTIVECAMERA_HPP_ */
