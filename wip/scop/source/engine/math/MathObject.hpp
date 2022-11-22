/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MathObject.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:33:33 by ecaceres          #+#    #+#             */
/*   Updated: 2022/11/13 18:33:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHOBJECT_HPP_
# define MATHOBJECT_HPP_

#include <engine/math/Matrix.hpp>
#include <engine/math/Vector.hpp>

template<typename T>
	struct MathObject
	{
		public:
			typedef T value_type;

			enum
			{
				size = 1
			};
	};

template<typename T, int N>
	struct MathObject<Vector<N, T>>
	{
		public:
			typedef T value_type;

			enum
			{
				size = N
			};
	};

template<typename T, int R, int C>
	struct MathObject<Matrix<R, C, T>>
	{
		public:
			typedef T value_type;

			enum
			{
				size = R * C
			};
	};

#endif /* MATHOBJECT_HPP_ */
