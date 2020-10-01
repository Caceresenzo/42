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
		min(const T &a, const T &b)
		{
			return (a < b ? a : b);
		}

	template<class T>
		inline const T&
		max(const T &a, const T &b)
		{
			return (a > b ? a : b);
		}

	template<class T>
		inline void
		swap(T &a, T &b)
		{
			T c = a;
			a = b;
			b = c;
		}

	template<class T>
		inline T
		abs(const T a)
		{
			return (a < 0 ? -a : a);
		}

	template<class InputIterator1, class InputIterator2>
		bool
		lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
		{
			while (first1 != last1)
			{
				if (first2 == last2 || *first2 < *first1)
					return (false);
				else if (*first1 < *first2)
					return (true);

				++first1;
				++first2;
			}

			return (first2 != last2);
		}

	template<class InputIterator1, class InputIterator2>
		bool
		equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
		{
			while (!(first1 == last1))
			{
				if (!(*first1 == *first2))
					return (false);

				++first1;
				++first2;
			}

			return (true);
		}
}

#endif /* ALGORITHM_HPP_ */
