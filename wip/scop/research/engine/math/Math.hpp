/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 23:02:38 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/27 23:02:38 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HPP_
# define MATH_HPP_

#include <cmath>

#define PI 3.14159265358979323846

class Math
{
	public:
		template<typename T>
			inline static T
			cos(const T &x)
			{
				return (std::cos(x));
			}

		template<typename T>
			inline static T
			sin(const T &x)
			{
				return (std::sin(x));
			}

		template<typename T>
			inline static T
			tan(const T &x)
			{
				return (std::tan(x));
			}

		template<typename T>
			inline static T
			sqrt(const T &x)
			{
				return (std::sqrt(x));
			}

		template<typename T>
			inline static T
			radians(const T &degrees)
			{
				return (degrees / 180.0 * PI);
			}
};

#endif /* MATH_HPP_ */
