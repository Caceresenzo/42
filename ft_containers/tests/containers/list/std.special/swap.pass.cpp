/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.pass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:35:33 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 17:35:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_list.hpp>

int
main(void)
{
	{
		Aware<int> a1[] = { 1, 3, 7, 9, 10 };
		Aware<int> a2[] = { 0, 2, 4, 5, 6, 8, 11 };

		LIST<Aware<int> > c1(a1, a1 + sizeof(a1) / sizeof(a1[0]));
		LIST<Aware<int> > c2(a2, a2 + sizeof(a2) / sizeof(a2[0]));

		SWAP(c1, c2);

		ASSERT(c1 == LIST<Aware<int> >(a2, a2 + sizeof(a2) / sizeof(a2[0])));
		ASSERT(c2 == LIST<Aware<int> >(a1, a1 + sizeof(a1) / sizeof(a1[0])));
	}

	ASSERT_AWARE_ZERO();

	{
		Aware<int> a1[] = { 1, 3, 7, 9, 10 };
		Aware<int> a2[] = { 0, 2, 4, 5, 6, 8, 11 };

		LIST<Aware<int> > c1(a1, a1);
		LIST<Aware<int> > c2(a2, a2 + sizeof(a2) / sizeof(a2[0]));

		SWAP(c1, c2);

		ASSERT(c1 == LIST<Aware<int> >(a2, a2 + sizeof(a2) / sizeof(a2[0])));
		ASSERT(c2.empty());
		ASSERT(DISTANCE(c2.begin(), c2.end()) == 0);
	}

	ASSERT_AWARE_ZERO();

	{
		Aware<int> a1[] = { 1, 3, 7, 9, 10 };
		Aware<int> a2[] = { 0, 2, 4, 5, 6, 8, 11 };

		LIST<Aware<int> > c1(a1, a1 + sizeof(a1) / sizeof(a1[0]));
		LIST<Aware<int> > c2(a2, a2);

		SWAP(c1, c2);

		ASSERT(c1.empty());
		ASSERT(DISTANCE(c1.begin(), c1.end()) == 0);
		ASSERT(c2 == LIST<Aware<int> >(a1, a1 + sizeof(a1) / sizeof(a1[0])));
	}

	ASSERT_AWARE_ZERO();

	{
		Aware<int> a1[] = { 1, 3, 7, 9, 10 };
		Aware<int> a2[] = { 0, 2, 4, 5, 6, 8, 11 };

		LIST<Aware<int> > c1(a1, a1);
		LIST<Aware<int> > c2(a2, a2);

		SWAP(c1, c2);

		ASSERT(c1.empty());
		ASSERT(DISTANCE(c1.begin(), c1.end()) == 0);
		ASSERT(c2.empty());
		ASSERT(DISTANCE(c2.begin(), c2.end()) == 0);
	}

	ASSERT_AWARE_ZERO();

	return (0);
}
