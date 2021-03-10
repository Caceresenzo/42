/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_comp.pass.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:38:18 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/09 15:38:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_list.hpp>

int
main()
{
	{
		int a1[] = { 10, 9, 7, 3, 1 };
		int a2[] = { 11, 8, 6, 5, 4, 2, 0 };
		int a3[] = { 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

		LIST<Aware<int> > c1(a1, a1 + sizeof(a1) / sizeof(a1[0]));
		LIST<Aware<int> > c2(a2, a2 + sizeof(a2) / sizeof(a2[0]));

		c1.merge(c2, std::greater<Aware<int> >());
		ASSERT(c1 == LIST<Aware<int> >(a3, a3 + sizeof(a3) / sizeof(a3[0])));
		ASSERT(c2.empty());
	}

	ASSERT_AWARE_ZERO();

	{
		int a1[] = { 10, 9, 7, 3, 1 };

		LIST<Aware<int> > c1(a1, a1 + sizeof(a1) / sizeof(a1[0]));

		c1.merge(c1, std::greater<Aware<int> >());
		ASSERT((c1 == LIST<Aware<int> >(a1, a1 + sizeof(a1) / sizeof(a1[0]))));
	}

	ASSERT_AWARE_ZERO();
}
