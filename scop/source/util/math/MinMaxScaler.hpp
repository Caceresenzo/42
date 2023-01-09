/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MinMaxScaler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:31:52 by ecaceres          #+#    #+#             */
/*   Updated: 2022/11/22 18:31:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINMAXSCALER_HPP_
# define MINMAXSCALER_HPP_

#include <lang/Math.hpp>
#include <limits>

template<typename T>
	struct MinMaxScaler
	{
		public:
			T min;
			T max;

		public:
			MinMaxScaler(const T &min = std::numeric_limits<float>::max(), const T &max = std::numeric_limits<float>::min()) :
				min(min),
				max(max)
			{
			}

		public:
			void
			fit(const T &value)
			{
				min = Math::min(min, value);
				max = Math::max(max, value);
			}

			T
			scale(const T &value)
			{
				return ((value - min) / (max - min));
			}
	};

#endif /* MINMAXSCALER_HPP_ */
