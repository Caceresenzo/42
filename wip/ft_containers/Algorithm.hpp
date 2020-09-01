/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 16:29:21 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/31 16:29:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP_
# define ALGORITHM_HPP_

#include <Utility.hpp>
#include <Iterator.hpp>
#include <stddef.h>

namespace ft
{
	template<class T, class S>
		void
		move(T *to, T *from, S len)
		{
			size_t index;

			for (index = 0; index < len; ++index)
				ft::construct_copy(&to[index], from[index]);

			for (index = 0; index < len; ++index)
				ft::destruct(from[index]);
		}

	template<class T>
		inline const T&
		max(const T &a, const T &b)
		{
			return (a < b ? b : a);
		}

	template<class T>
		inline void
		swap(T &a, T &b)
		{
			T c = a;
			a = b;
			b = c;
		}
}

#endif /* ALGORITHM_HPP_ */
