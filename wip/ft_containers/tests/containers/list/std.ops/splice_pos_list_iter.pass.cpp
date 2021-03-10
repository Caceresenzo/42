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
	return (0);
	int a1[] = {1, 2, 3};
	int a2[] = {4, 5, 6};

	{
		LIST<Aware<int> > l1;
		LIST<Aware<int> > l2(a2, a2 + 1);
		l1.splice(l1.end(), l2, l2.begin());
		ASSERT(l1.size() == 1);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 1);
		ASSERT(l2.size() == 0);
		ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
		LIST<Aware<int> >::const_iterator i = l1.begin();
		ASSERT(*i == 4);
	}

	ASSERT_AWARE_ZERO();

	{
		LIST<Aware<int> > l1;
		LIST<Aware<int> > l2(a2, a2 + 2);
		l1.splice(l1.end(), l2, l2.begin());
		ASSERT(l1.size() == 1);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 1);
		ASSERT(l2.size() == 1);
		ASSERT(DISTANCE(l2.begin(), l2.end()) == 1);
		LIST<Aware<int> >::const_iterator i = l1.begin();
		ASSERT(*i == 4);
		i = l2.begin();
		ASSERT(*i == 5);
	}

	ASSERT_AWARE_ZERO();

	{
		LIST<Aware<int> > l1;
		LIST<Aware<int> > l2(a2, a2 + 2);
		l1.splice(l1.end(), l2, NEXT(l2.begin()));
		ASSERT(l1.size() == 1);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 1);
		ASSERT(l2.size() == 1);
		ASSERT(DISTANCE(l2.begin(), l2.end()) == 1);
		LIST<Aware<int> >::const_iterator i = l1.begin();
		ASSERT(*i == 5);
		i = l2.begin();
		ASSERT(*i == 4);
	}

	ASSERT_AWARE_ZERO();

	{
		LIST<Aware<int> > l1;
		LIST<Aware<int> > l2(a2, a2 + 3);
		l1.splice(l1.end(), l2, l2.begin());
		ASSERT(l1.size() == 1);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 1);
		ASSERT(l2.size() == 2);
		ASSERT(DISTANCE(l2.begin(), l2.end()) == 2);
		LIST<Aware<int> >::const_iterator i = l1.begin();
		ASSERT(*i == 4);
		i = l2.begin();
		ASSERT(*i == 5);
		++i;
		ASSERT(*i == 6);
	}

	ASSERT_AWARE_ZERO();

	{
		LIST<Aware<int> > l1;
		LIST<Aware<int> > l2(a2, a2 + 3);
		l1.splice(l1.end(), l2, NEXT(l2.begin()));
		ASSERT(l1.size() == 1);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 1);
		ASSERT(l2.size() == 2);
		ASSERT(DISTANCE(l2.begin(), l2.end()) == 2);
		LIST<Aware<int> >::const_iterator i = l1.begin();
		ASSERT(*i == 5);
		i = l2.begin();
		ASSERT(*i == 4);
		++i;
		ASSERT(*i == 6);
	}

	ASSERT_AWARE_ZERO();

	{
		LIST<Aware<int> > l1;
		LIST<Aware<int> > l2(a2, a2 + 3);
		l1.splice(l1.end(), l2, NEXT(l2.begin(), 2));
		ASSERT(l1.size() == 1);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 1);
		ASSERT(l2.size() == 2);
		ASSERT(DISTANCE(l2.begin(), l2.end()) == 2);
		LIST<Aware<int> >::const_iterator i = l1.begin();
		ASSERT(*i == 6);
		i = l2.begin();
		ASSERT(*i == 4);
		++i;
		ASSERT(*i == 5);
	}

	ASSERT_AWARE_ZERO();

	{
		LIST<Aware<int> > l1(a1, a1 + 1);
		l1.splice(l1.begin(), l1, l1.begin());
		ASSERT(l1.size() == 1);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 1);
		LIST<Aware<int> >::const_iterator i = l1.begin();
		ASSERT(*i == 1);
	}

	ASSERT_AWARE_ZERO();

	{
		LIST<Aware<int> > l1(a1, a1 + 1);
		LIST<Aware<int> > l2(a2, a2 + 1);
		l1.splice(l1.begin(), l2, l2.begin());
		ASSERT(l1.size() == 2);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 2);
		ASSERT(l2.size() == 0);
		ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
		LIST<Aware<int> >::const_iterator i = l1.begin();
		ASSERT(*i == 4);
		++i;
		ASSERT(*i == 1);
	}

	ASSERT_AWARE_ZERO();

	{
		LIST<Aware<int> > l1(a1, a1 + 1);
		LIST<Aware<int> > l2(a2, a2 + 1);
		l1.splice(NEXT(l1.begin()), l2, l2.begin());
		ASSERT(l1.size() == 2);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 2);
		ASSERT(l2.size() == 0);
		ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
		LIST<Aware<int> >::const_iterator i = l1.begin();
		ASSERT(*i == 1);
		++i;
		ASSERT(*i == 4);
	}

	ASSERT_AWARE_ZERO();

	{
		LIST<Aware<int> > l1(a1, a1 + 2);
		l1.splice(l1.begin(), l1, l1.begin());
		ASSERT(l1.size() == 2);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 2);
		LIST<Aware<int> >::const_iterator i = l1.begin();
		ASSERT(*i == 1);
		++i;
		ASSERT(*i == 2);
	}

	ASSERT_AWARE_ZERO();

	{
		LIST<Aware<int> > l1(a1, a1 + 2);
		l1.splice(l1.begin(), l1, NEXT(l1.begin()));
		ASSERT(l1.size() == 2);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 2);
		LIST<Aware<int> >::const_iterator i = l1.begin();
		ASSERT(*i == 2);
		++i;
		ASSERT(*i == 1);
	}

	ASSERT_AWARE_ZERO();

	{
		LIST<Aware<int> > l1(a1, a1 + 2);
		l1.splice(NEXT(l1.begin()), l1, l1.begin());
		ASSERT(l1.size() == 2);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 2);
		LIST<Aware<int> >::const_iterator i = l1.begin();
		ASSERT(*i == 1);
		++i;
		ASSERT(*i == 2);
	}

	ASSERT_AWARE_ZERO();

	{
		LIST<Aware<int> > l1(a1, a1 + 2);
		l1.splice(NEXT(l1.begin()), l1, NEXT(l1.begin()));
		ASSERT(l1.size() == 2);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 2);
		LIST<Aware<int> >::const_iterator i = l1.begin();
		ASSERT(*i == 1);
		++i;
		ASSERT(*i == 2);
	}

	ASSERT_AWARE_ZERO();
}
