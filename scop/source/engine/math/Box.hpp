/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Box.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:12:25 by ecaceres          #+#    #+#             */
/*   Updated: 2022/11/14 16:12:25 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOX_HPP_
# define BOX_HPP_

#include <engine/math/Vector.hpp>

template<int N, typename T>
	struct BoundingBox
	{
		public:
			Vector<N, T> min;
			Vector<N, T> max;

		public:
			BoundingBox(Vector<N, T> min, Vector<N, T> max) :
				min(min),
				max(max)
			{
			}

		public:
			Vector<N, T>
			center() const
			{
				return (::abs((min + max) / 2.0f));
			}
	};

#endif /* BOX_HPP_ */
