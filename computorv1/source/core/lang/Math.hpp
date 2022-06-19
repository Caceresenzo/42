/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:22:05 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/05 21:22:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HPP_
# define MATH_HPP_

class Math
{
	public:
		template<typename T>
			static T
			sqrt(const T &n)
			{
				if (n <= 0)
					return (0);

				T tmp = 0;
				T sqrt = n / 2;

				while (sqrt != tmp)
				{
					tmp = sqrt;
					sqrt = (n / sqrt + sqrt) / 2;
				}

				return (sqrt);
			}
};

#endif /* MATH_HPP_ */
