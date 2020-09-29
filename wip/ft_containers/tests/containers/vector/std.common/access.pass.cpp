/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.pass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:35:49 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 18:35:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_vector.hpp>

template<class C>
	C
	make(int size, int start = 0)
	{
		C c;
		for (int i = 0; i < size; ++i)
			c.push_back(start + i);

		return (c);
	}

int
main(void)
{
	TEST_AWARE_BLOCK({
		typedef VECTOR<Aware<int> > C;
		C c = make<C>(10);

		ASSERT_NOEXCEPT(c[0]);
		ASSERT_NOEXCEPT(c.at(0));
		ASSERT_NOEXCEPT(c.front());
		ASSERT_NOEXCEPT(c.back());

		for (int i = 0; i < 10; ++i)
			ASSERT(c[i] == i);

		for (int i = 0; i < 10; ++i)
			ASSERT(c.at(i) == i);

		ASSERT(c.front() == 0);
		ASSERT(c.back() == 9);
	});

	TEST_AWARE_BLOCK({
		typedef VECTOR<Aware<int> > C;
		const int N = 5;
		const C c = make<C>(10, N);

		ASSERT_NOEXCEPT(c[0]);
		ASSERT_NOEXCEPT(c.at(0));
		ASSERT_NOEXCEPT(c.front());
		ASSERT_NOEXCEPT(c.back());

		for (int i = 0; i < 10; ++i)
			ASSERT(c[i] == N + i);

		for (int i = 0; i < 10; ++i)
			ASSERT(c.at(i) == N + i);

		ASSERT(c.front() == N);
		ASSERT(c.back() == N + 9);
	});

	return (0);
}
