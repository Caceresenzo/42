/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.pass.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:30:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 18:30:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Vector.hpp>
#include <test_macros.hpp>

struct A
{
		int first;
		int second;
};

int
main(int, char**)
{
	TEST_AWARE_BLOCK({
		typedef Aware<int> T;
		typedef ft::Vector<T> C;
		C c;
		C::iterator i = c.begin();
		C::iterator j = c.end();

		ASSERT(i == j);
	});

	TEST_AWARE_BLOCK({
		typedef Aware<int> T;
		typedef ft::Vector<T> C;
		const C c;

		C::const_iterator i = c.begin();
		C::const_iterator j = c.end();
		ASSERT(i == j);
	});

	{ /* Aware block is not usable here for some reason. */
		typedef Aware<int> T;
		typedef ft::Vector<T> C;
		const T t[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		C c(t, t + (sizeof(t) / sizeof(t[0])));
		C::iterator i = c.begin();

		ASSERT(*i == 0);

		++i;
		ASSERT(*i == 1);

		*i = 10;
		ASSERT(*i == 10);
	}

	ASSERT_AWARE_ZERO();

	TEST_AWARE_BLOCK({
		typedef Aware<int> T;
		typedef ft::Vector<T> C;
		C::iterator i;
		C::const_iterator j;

		(void)i;
		(void)j;
	});

	return (0);
}
