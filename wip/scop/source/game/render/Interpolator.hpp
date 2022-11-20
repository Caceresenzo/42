/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interpolator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 22:54:27 by ecaceres          #+#    #+#             */
/*   Updated: 2022/11/20 22:54:27 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPOLATOR_HPP_
# define INTERPOLATOR_HPP_

#include <list>

template<typename T>
	class Interpolator
	{
		public:
			T start;
			T end;
			T step;
			T value;

		public:
			Interpolator(T start, T end, T step) :
				start(start),
				end(end),
				step(step),
				value()
			{
			}

			Interpolator(T start, T end, T step, T initial_value) :
				start(start),
				end(end),
				step(step),
				value(initial_value)
			{
			}

		public:
			void
			tick(double delta_time = 1.0)
			{
				/* decrement */
				if (start > end)
				{
					if (value > end)
						value -= step * delta_time;
					else
						value = end;
				}

				/* increment */
				else if (start < end)
				{
					if (value < end)
						value += step * delta_time;
					else
						value = end;
				}

				/* equal */
				else
					value = end;
			}

			void
			reverse()
			{
				std::swap(start, end);
			}
	};

#endif /* INTERPOLATOR_HPP_ */
