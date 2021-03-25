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

	template<class T, class S>
		inline void
		destruct(T *ptr, S n)
		{
			while (n--)
				(ptr++)->~T();
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
		inline void
		construct_by_copy(T *ptr, const T &ref)
		{
			::new (ptr++) T(ref);
		}

	template<class T, class S>
		inline void
		construct_n_by_copy(T *ptr, const T &ref, S n)
		{
			while (n--)
				::new (ptr++) T(ref);
		}

	template<class T, class U, class S>
		inline void
		construct_all_by_copy(T *to, U *from, S n)
		{
			while (n--)
				construct_by_copy(to++, *from++);
		}

	template<class I, class O>
		inline O
		copy(I first, I last, O dest_first)
		{
			while (first != last)
				*dest_first++ = *first++;

			return (dest_first);
		}

	template<class I, class O>
		O
		copy_backward(I first, I last, O dest_last)
		{
			while (first != last)
				*(--dest_last) = *(--last);

			return (dest_last);
		}

	/**
	 * This class couples together a pair of values, which may be of different types (T1 and T2). The individual values can be accessed through its public members first and second.
	 *
	 * @tparam T1 Type of member first, aliased as first_type.
	 * @tparam T2 Type of member second, aliased as second_type.
	 */
	template<class T1, class T2>
		struct pair
		{
			public:
				/** The first template parameter (T1). */
				typedef T1 first_type;

				/** The second template parameter (T2). */
				typedef T2 second_type;

			public:
				first_type first;
				second_type second;

			public:
				/**
				 * Constructs a pair object with its elements value-initialized.
				 */
				pair()
				{
				}

				/**
				 * The object is initialized with the contents of the pr pair object.
				 *
				 * @param pr Another pair object.
				 */
				template<class U, class V>
					pair(const pair<U, V> &pr) :
							first(pr.first),
							second(pr.second)
					{
					}

				/**
				 *
				 * @param a An object of the type of first, or some other type implicitly convertible to it.
				 * @param b An object of the type of second, or some other type implicitly convertible to it.
				 */
				pair(const first_type &a, const second_type &b) :
						first(a),
						second(b)
				{
				}

				pair&
				operator=(const pair &pr)
				{
					first = pr.first;
					second = pr.second;

					return (*this);
				}
		};

	template<class T1, class T2>
		bool
		operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
		{
			return (lhs.first == rhs.first && lhs.second == rhs.second);
		}

	/**
	 * Constructs a pair object with its first element set to x and its second element set to y.
	 *
	 * @tparam T1 Type of member first.
	 * @tparam T2 Type of member second.
	 * @param x Value for the first member of the pair object being constructed.
	 * @param y Value for the second member of the pair object being constructed.
	 */
	template<class T1, class T2>
		pair<T1, T2>
		make_pair(T1 x, T2 y)
		{
			return (pair<T1, T2>(x, y));
		}
}

#endif /* FT_UTILITY_HPP_ */
