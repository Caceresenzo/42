/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 13:24:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/09/01 13:24:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Algorithm.hpp>
#include <Iterator.hpp>
#include <Vector.hpp>
#include <test_macros.hpp>

int
main(void)
{
	{
		Aware<int> a1[] = { 1, 3, 7, 9, 10 };
		Aware<int> a2[] = { 0, 2, 4, 5, 6, 8, 11 };

		ft::Vector<Aware<int> > c1(a1, a1 + sizeof(a1) / sizeof(a1[0]));
		ft::Vector<Aware<int> > c2(a2, a2 + sizeof(a2) / sizeof(a2[0]));

		swap(c1, c2);

		ASSERT(c1 == ft::Vector<Aware<int> >(a2, a2 + sizeof(a2) / sizeof(a2[0])));
		ASSERT(c2 == ft::Vector<Aware<int> >(a1, a1 + sizeof(a1) / sizeof(a1[0])));
	}

	ASSERT_AWARE_ZERO();

	{
		Aware<int> a1[] = { 1, 3, 7, 9, 10 };
		Aware<int> a2[] = { 0, 2, 4, 5, 6, 8, 11 };

		ft::Vector<Aware<int> > c1(a1, a1);
		ft::Vector<Aware<int> > c2(a2, a2 + sizeof(a2) / sizeof(a2[0]));

		swap(c1, c2);

		ASSERT(c1 == ft::Vector<Aware<int> >(a2, a2 + sizeof(a2) / sizeof(a2[0])));
		ASSERT(c2.empty());
		ASSERT((c2.end() - c2.begin()) == 0);
	}

	ASSERT_AWARE_ZERO();

	{
		Aware<int> a1[] = { 1, 3, 7, 9, 10 };
		Aware<int> a2[] = { 0, 2, 4, 5, 6, 8, 11 };

		ft::Vector<Aware<int> > c1(a1, a1 + sizeof(a1) / sizeof(a1[0]));
		ft::Vector<Aware<int> > c2(a2, a2);

		swap(c1, c2);

		ASSERT(c1.empty());
		ASSERT((c1.end() - c1.begin()) == 0);
		ASSERT(c2 == ft::Vector<Aware<int> >(a1, a1 + sizeof(a1) / sizeof(a1[0])));
	}

	ASSERT_AWARE_ZERO();

	{
		Aware<int> a1[] = { 1, 3, 7, 9, 10 };
		Aware<int> a2[] = { 0, 2, 4, 5, 6, 8, 11 };

		ft::Vector<Aware<int> > c1(a1, a1);
		ft::Vector<Aware<int> > c2(a2, a2);

		swap(c1, c2);

		ASSERT(c1.empty());
		ASSERT((c1.end() - c1.begin()) == 0);
		ASSERT(c2.empty());
		ASSERT((c2.end() - c2.begin()) == 0);
	}

	ASSERT_AWARE_ZERO();

	{
		Aware<int> a1[] = { 1, 3, 7, 9, 10 };
		Aware<int> a2[] = { 0, 2, 4, 5, 6, 8, 11 };

		ft::Vector<Aware<int> > c1(a1, a1 + sizeof(a1) / sizeof(a1[0]));
		ft::Vector<Aware<int> > c2(a2, a2 + sizeof(a2) / sizeof(a2[0]));

		swap(c1, c2);

		ASSERT((c1 == ft::Vector<Aware<int> >(a2, a2 + sizeof(a2) / sizeof(a2[0]))));
		ASSERT((c2 == ft::Vector<Aware<int> >(a1, a1 + sizeof(a1) / sizeof(a1[0]))));
	}

	ASSERT_AWARE_ZERO();

	{
		Aware<int> a1[] = { 1, 3, 7, 9, 10 };
		Aware<int> a2[] = { 0, 2, 4, 5, 6, 8, 11 };

		ft::Vector<Aware<int> > c1(a1, a1 + sizeof(a1) / sizeof(a1[0]));
		ft::Vector<Aware<int> > c2(a2, a2 + sizeof(a2) / sizeof(a2[0]));

		swap(c1, c2);

		ASSERT((c1 == ft::Vector<Aware<int> >(a2, a2 + sizeof(a2) / sizeof(a2[0]))));
		ASSERT((c2 == ft::Vector<Aware<int> >(a1, a1 + sizeof(a1) / sizeof(a1[0]))));
	}

	ASSERT_AWARE_ZERO();

	return (0);
}
