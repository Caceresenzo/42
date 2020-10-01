/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_iter_iter.pass.cpp                           :+:      :+:    :+:   */
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
		Aware<int> a1[] = { 1, 2, 3 };
		LIST<Aware<int> > l1(a1, a1 + 3);
		LIST<Aware<int> >::iterator i = l1.erase(l1.begin(), l1.begin());

		ASSERT(l1.size() == 3);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 3);
		ASSERT(i == l1.begin());
	}

	ASSERT_AWARE_ZERO();

	{
		Aware<int> a1[] = { 1, 2, 3 };
		LIST<Aware<int> > l1(a1, a1 + 3);
		LIST<Aware<int> >::iterator i = l1.erase(l1.begin(), ft::next(l1.begin()));

		ASSERT(l1.size() == 2);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 2);
		ASSERT(i == l1.begin());
		ASSERT(l1 == LIST<Aware<int> >(a1 + 1, a1 + 3));
	}

	ASSERT_AWARE_ZERO();

	{
		Aware<int> a1[] = { 1, 2, 3 };
		LIST<Aware<int> > l1(a1, a1 + 3);
		LIST<Aware<int> >::iterator i = l1.erase(l1.begin(), ft::next(l1.begin(), 2));

		ASSERT(l1.size() == 1);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 1);
		ASSERT(i == l1.begin());
		ASSERT(l1 == LIST<Aware<int> >(a1 + 2, a1 + 3));
	}

	ASSERT_AWARE_ZERO();

	{
		Aware<int> a1[] = { 1, 2, 3 };
		LIST<Aware<int> > l1(a1, a1 + 3);
		LIST<Aware<int> >::iterator i = l1.erase(l1.begin(), ft::next(l1.begin(), 3));

		ASSERT(l1.size() == 0);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 0);
		ASSERT(i == l1.begin());
	}

	ASSERT_AWARE_ZERO();

	return (0);
}
