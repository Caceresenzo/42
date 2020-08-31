/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 15:11:07 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/31 15:11:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILITY_HPP_
# define FT_UTILITY_HPP_

namespace ft
{
	template<class T>
		inline void
		destruct(T *ptr)
		{
			ptr->~T();
		}

	template<class T>
		inline void
		destruct(T &ref)
		{
			ref.~T();
		}

	template<class T>
		inline T*
		construct(T *ptr)
		{
			::new (ptr) T();

			return (ptr);
		}

	template<class T, class S>
		inline T*
		construct(T *ptr, S n)
		{
			while (n--)
				::new (ptr++) T();

			return (ptr);
		}

	template<class T>
		inline T*
		construct_copy(T *ptr, const T &ref)
		{
			::new (ptr++) T(ref);

			return (ptr);
		}

	template<class T, class S>
		inline T*
		construct_copy(T *ptr, const T &ref, S n)
		{
			while (n--)
				::new (ptr++) T(ref);

			return (ptr);
		}
}

#endif /* FT_UTILITY_HPP_ */
