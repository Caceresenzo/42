/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 11:57:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/14 11:57:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>

#define xassert(exp) \
	{ \
		if ((exp)) \
			std::cout << "\e[92mPASSED\e[39m: " << #exp << std::endl; \
		else { \
			std::cout << "\e[91mFAILED\e[39m: " << #exp << "    (line: " << __LINE__ << ")" << std::endl; \
			exit(1); \
		} \
	}

template<typename T>
	void
	swap(T &a, T &b)
	{
		T c = a;
		a = b;
		b = c;
	}

template<typename T>
	T const
	&min(T const &a, T const &b)
	{
		return (a < b ? a : b);
	}

template<typename T>
	T const
	&max(T const &a, T const &b)
	{
		return (a > b ? a : b);
	}

int
main(void)
{
	std::cout << "--- SWAP ---" << std::endl;

	{
		int a = 5, b = 6;

		swap(a, b);
		xassert(a == 6 && b == 5)

		swap(a, b);
		xassert(a == 5 && b == 6)
	}
	{
		size_t a = 5, b = 6;

		swap(a, b);
		xassert(a == 6 && b == 5)

		swap(a, b);
		xassert(a == 5 && b == 6)
	}
	{
		double a = 5.0, b = 6.0;

		swap(a, b);
		xassert(a == 6.0 && b == 5.0)

		swap(a, b);
		xassert(a == 5.0 && b == 6.0)
	}

	std::cout << std::endl << "--- MIN ---" << std::endl;

	{
		int a = 5, b = 6;

		xassert(min(a, b) == 5)
	}
	{
		size_t a = 5, b = 6;

		xassert(min(a, b) == 5)
	}
	{
		double a = 5.0, b = 6.0;

		xassert(min(a, b) == 5.0)
	}

	std::cout << std::endl << "--- MAX ---" << std::endl;

	{
		int a = 5, b = 6;

		xassert(max(a, b) == 6)
	}
	{
		size_t a = 5, b = 6;

		xassert(max(a, b) == 6)
	}
	{
		double a = 5.0, b = 6.0;

		xassert(max(a, b) == 6.0)
	}

	std::cout << std::endl << "--- 42 ---" << std::endl;

	{
		int a = 2;
		int b = 3;
		swap(a, b);
		std::cout << "a = " << a << ", b = " << b << std::endl;
		std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
		std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;
		std::string c = "chaine1";
		std::string d = "chaine2";
		swap(c, d);
		std::cout << "c = " << c << ", d = " << d << std::endl;
		std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
		std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;
	}
	return 0;
}
