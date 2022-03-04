/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICamera.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:36:41 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/27 21:36:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICAMERA_HPP_
# define ICAMERA_HPP_

#include <engine/math/matrix.hpp>

class ICamera
{
	public:
		ICamera();

		virtual
		~ICamera();

	public:
		virtual const Vector<3, float>&
		position() const = 0;

		virtual float
		yaw() const = 0;

		virtual float
		pitch() const = 0;

		virtual const Matrix<4, 4, float>&
		view_matrix() const = 0;

		virtual void
		move(double delta) = 0;

		virtual void
		look(const Vector<2, int> &offset) = 0;
};

#endif /* ICAMERA_HPP_ */
