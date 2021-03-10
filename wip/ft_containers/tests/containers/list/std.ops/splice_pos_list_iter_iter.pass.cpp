/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splice_pos_list_iter.pass.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:50:04 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/09 15:50:04 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_list.hpp>

int
main(void)
{
	int a1[] = {1, 2, 3};
	int a2[] = {4, 5, 6};

	{
		LIST<int> l1(a1, a1 + 3);
		l1.splice(l1.begin(), l1, NEXT(l1.begin()), NEXT(l1.begin()));
		ASSERT(l1.size() == 3);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 3);
		LIST<int>::const_iterator i = l1.begin();
		ASSERT(*i == 1);
		++i;
		ASSERT(*i == 2);
		++i;
		ASSERT(*i == 3);
	}
	{
		LIST<int> l1(a1, a1 + 3);
		l1.splice(l1.begin(), l1, NEXT(l1.begin()), NEXT(l1.begin(), 2));
		ASSERT(l1.size() == 3);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 3);
		LIST<int>::const_iterator i = l1.begin();
		ASSERT(*i == 2);
		++i;
		ASSERT(*i == 1);
		++i;
		ASSERT(*i == 3);
	}
	{
		LIST<int> l1(a1, a1 + 3);
		l1.splice(l1.begin(), l1, NEXT(l1.begin()), NEXT(l1.begin(), 3));
		ASSERT(l1.size() == 3);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 3);
		LIST<int>::const_iterator i = l1.begin();
		ASSERT(*i == 2);
		++i;
		ASSERT(*i == 3);
		++i;
		ASSERT(*i == 1);
	}
	{
		LIST<int> l1(a1, a1 + 3);
		LIST<int> l2(a2, a2 + 3);
		l1.splice(l1.begin(), l2, NEXT(l2.begin()), l2.end());
		ASSERT(l1.size() == 5);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 5);
		LIST<int>::const_iterator i = l1.begin();
		ASSERT(*i == 5);
		++i;
		ASSERT(*i == 6);
		++i;
		ASSERT(*i == 1);
		++i;
		ASSERT(*i == 2);
		++i;
		ASSERT(*i == 3);
		ASSERT(l2.size() == 1);
		i = l2.begin();
		ASSERT(*i == 4);
	}
	{
		LIST<int> l1(a1, a1 + 3);
		LIST<int> l2(a2, a2 + 3);
		l1.splice(NEXT(l1.begin()), l2, NEXT(l2.begin()), l2.end());
		ASSERT(l1.size() == 5);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 5);
		LIST<int>::const_iterator i = l1.begin();
		ASSERT(*i == 1);
		++i;
		ASSERT(*i == 5);
		++i;
		ASSERT(*i == 6);
		++i;
		ASSERT(*i == 2);
		++i;
		ASSERT(*i == 3);
		ASSERT(l2.size() == 1);
		i = l2.begin();
		ASSERT(*i == 4);
	}
	{
		LIST<int> l1(a1, a1 + 3);
		LIST<int> l2(a2, a2 + 3);
		l1.splice(l1.end(), l2, NEXT(l2.begin()), l2.end());
		ASSERT(l1.size() == 5);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 5);
		LIST<int>::const_iterator i = l1.begin();
		ASSERT(*i == 1);
		++i;
		ASSERT(*i == 2);
		++i;
		ASSERT(*i == 3);
		++i;
		ASSERT(*i == 5);
		++i;
		ASSERT(*i == 6);
		ASSERT(l2.size() == 1);
		i = l2.begin();
		ASSERT(*i == 4);
	}
}
