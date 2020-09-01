/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TypeTraits.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:40:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/09/01 16:40:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPETRAITS_HPP_
# define TYPETRAITS_HPP_

namespace ft
{

	template<bool Condition, typename T = void>
		struct enable_if
		{
		};

	template<typename T>
		struct enable_if<true, T>
		{
				typedef T type;
		};

	template<typename T>
		struct is_integral
		{
				static const bool value = false;
		};

	template<>
		struct is_integral<bool>
		{
				static const bool value = true;
		};

	template<>
		struct is_integral<char>
		{
				static const bool value = true;
		};

	template<>
		struct is_integral<wchar_t>
		{
				static const bool value = true;
		};

	template<>
		struct is_integral<signed char>
		{
				static const bool value = true;
		};

	template<>
		struct is_integral<short int>
		{
				static const bool value = true;
		};

	template<>
		struct is_integral<int>
		{
				static const bool value = true;
		};

	template<>
		struct is_integral<long int>
		{
				static const bool value = true;
		};

	template<>
		struct is_integral<long long int>
		{
				static const bool value = true;
		};

	template<>
		struct is_integral<unsigned char>
		{
				static const bool value = true;
		};

	template<>
		struct is_integral<unsigned short int>
		{
				static const bool value = true;
		};

	template<>
		struct is_integral<unsigned int>
		{
				static const bool value = true;
		};

	template<>
		struct is_integral<unsigned long int>
		{
				static const bool value = true;
		};

	template<>
		struct is_integral<unsigned long long int>
		{
				static const bool value = true;
		};

}

#endif /* TYPETRAITS_HPP_ */
