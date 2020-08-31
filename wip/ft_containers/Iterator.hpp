/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:27:27 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/25 17:27:27 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP_
# define ITERATOR_HPP_

# include <cstddef>

namespace ft
{
	struct input_iterator_tag
	{
	};

	struct output_iterator_tag
	{
	};

	struct forward_iterator_tag :
	        input_iterator_tag
	{
	};

	struct bidirectional_iterator_tag :
	        forward_iterator_tag
	{
	};

	struct random_access_iterator_tag :
	        bidirectional_iterator_tag
	{
	};

	template<class Category, class T, class Distance = ptrdiff_t,
	        class Pointer = T*, class Reference = T&>
		struct iterator
		{
				typedef T value_type;
				typedef Distance difference_type;
				typedef Pointer pointer;
				typedef Reference reference;
				typedef Category iterator_category;
		};

	template<class T>
		struct remove_pointer
		{
				typedef T type;
		};

	template<class T>
		struct remove_pointer<T*>
		{
				typedef T type;
		};

	template<class T>
		struct remove_pointer<T* const >
		{
				typedef T type;
		};

	template<class T>
		struct remove_pointer<T* volatile >
		{
				typedef T type;
		};

	template<class T>
		struct remove_pointer<T* const volatile >
		{
				typedef T type;
		};

	template<class T>
		struct remove_const
		{
				typedef T type;
		};
	template<class T>
		struct remove_const<const T>
		{
				typedef T type;
		};

	template<class T>
		struct remove_volatile
		{
				typedef T type;
		};

	template<class T>
		struct remove_volatile<volatile T>
		{
				typedef T type;
		};

	template<class T>
		struct remove_cv
		{
				typedef typename remove_volatile<
				        typename remove_const<T>::type>::type type;
		};

	template<class _Iter>
		struct iterator_traits
		{
		};

	template<class T>
		struct iterator_traits<T*>
		{
				typedef ptrdiff_t difference_type;
				typedef typename remove_cv<T>::type value_type;
				typedef T *pointer;
				typedef T &reference;
				typedef random_access_iterator_tag iterator_category;
		};
}

#endif /* ITERATOR_HPP_ */
