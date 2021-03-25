/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.pass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:18:00 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/08 23:18:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Iterator.hpp>
#include <List.hpp>
#include <support_std.hpp>
#include <test_macros.hpp>
#include <unit_list.hpp>
#include <unit_vector.hpp>
#include <Vector.hpp>
#include <cstdlib>
#include <iostream>

namespace tester
{
	template<class RandomIt>
		void
		random_shuffle(RandomIt first, RandomIt last)
		{
			typename ITERATOR_TRAITS<RandomIt>::difference_type i, n;
			n = last - first;
			for (i = n - 1; i > 0; --i)
			{
				SWAP(first[i], first[std::rand() % (i + 1)]);
			}
		}
}

struct Payload
{
		int val;
		int side;

		Payload(int v) :
				val(v),
				side(0)
		{
		}

		Payload(int v, int s) :
				val(v),
				side(s)
		{
		}

		bool
		operator<(const Payload &rhs) const
		{
			return val < rhs.val;
		}
};

std::ostream&
operator <<(std::ostream &stream, const Payload &payload)
{
	return (stream << payload.val);
}

void
test_stable(int N)
{
	typedef Payload T;
	typedef LIST<T> C;
	typedef VECTOR<T> V;
	V v;

	for (int i = 0; i < N; ++i)
		v.push_back(Payload(i / 2));

	tester::random_shuffle(v.begin(), v.end());

	for (int i = 0; i < N; ++i)
		v[i].side = i;

	C c(v.begin(), v.end());
	c.sort();

	ASSERT(DISTANCE(c.begin(), c.end()) == N);

	C::const_iterator j = c.begin();
	for (int i = 0; i < N; ++i, ++j)
		ASSERT(j->val == i / 2);

	for (C::const_iterator it = c.begin(); it != c.end(); ++it)
	{
		C::const_iterator next = NEXT(it);
		if (next != c.end() && it->val == next->val)
			ASSERT(it->side < next->side);
	}
}

int
main(void)
{
	{
		int a1[] = { 4, 8, 1, 0, 5, 7, 2, 3, 6, 11, 10, 9 };
		int a2[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

		LIST<Aware<int> > c1(a1, a1 + sizeof(a1) / sizeof(a1[0]));
		LIST<Aware<int> > c2(a2, a2 + sizeof(a2) / sizeof(a2[0]));

		c1.sort();

		if (false)
		{
			LIST<Aware<int> >::iterator it;
			for (it = c1.begin(); it != c1.end(); it++)
				std::cout << *it << "  " << std::flush;
			std::cout << std::endl;
			std::cout << std::endl;
			it--;
			for (; it != PREV(c1.begin(), 1); it--)
				std::cout << *it << "  " << std::flush;
		}

		ASSERT(c1 == c2);
	}

	ASSERT_AWARE_ZERO();

	srand (
	time(NULL));for
(	int i = 0; i < 40; ++i)
	test_stable(i);
}
