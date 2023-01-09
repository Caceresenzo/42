/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Transform.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 00:19:28 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 00:19:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_HPP_
# define TRANSFORM_HPP_

#include <engine/math/Matrix.hpp>
#include <engine/math/Vector.hpp>

template<typename T = float>
	class Transform
	{
		public:
			Vector<3, T> translation;
			Vector<3, T> rotation;
			Vector<3, T> scaling;

		public:
			Transform() :
					translation(0),
					rotation(0),
					scaling(1)
			{
			}

		public:
			Matrix<4, 4, T>
			model() const
			{
				return (::scale(::rotate(::translate(Matrix<4, 4, T>(1), translation), rotation), scaling));
			}
	};

#endif /* TRANSFORM_HPP_ */
