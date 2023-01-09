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

#include <lang/ArithmeticException.hpp>
#include <cmath>
#include <algorithm>
#include <cerrno>

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

		template<typename T>
			inline static T
			min(const T &a, const T &b)
			{
				return (std::min(a, b));
			}

		template<typename T>
			inline static T
			max(const T &a, const T &b)
			{
				return (std::max(a, b));
			}

		template<typename T>
			inline static T
			clamp(const T &value, const T &low, const T &high)
			{
				return (Math::max(low, Math::min(high, value)));
			}

		template<typename T>
			inline static T
			abs(const T &value)
			{
				return (std::abs(value));
			}

		template<typename T>
			inline static T
			floating_modulo(const T &number, const T &denom)
			{
				T answer = std::fmod(number, denom);

				if (errno == EDOM)
					throw ArithmeticException("argument out of domain");

				return (answer);
			}
};

#endif /* MATH_HPP_ */
