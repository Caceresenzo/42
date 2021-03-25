/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splice_pos_list.pass.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:47:11 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/08 16:47:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_list.hpp>

int
main(void)
{
	{
		Aware<int> a1[] = { 1, 2, 3 };
		Aware<int> a2[] = { 4, 5, 6 };

		{
			LIST<Aware<int> > l1;
			LIST<Aware<int> > l2;
			l1.splice(l1.end(), l2);
			ASSERT(l1.size() == 0);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 0);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
		}

		{
			LIST<Aware<int> > l1;
			LIST<Aware<int> > l2(a2, a2 + 1);
			l1.splice(l1.end(), l2);
			ASSERT(l1.size() == 1);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 1);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 4);
		}

		{
			LIST<Aware<int> > l1;
			LIST<Aware<int> > l2(a2, a2 + 2);
			l1.splice(l1.end(), l2);
			ASSERT(l1.size() == 2);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 2);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 5);
		}

		{
			LIST<Aware<int> > l1;
			LIST<Aware<int> > l2(a2, a2 + 3);
			l1.splice(l1.end(), l2);
			ASSERT(l1.size() == 3);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 3);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 5);
			++i;
			ASSERT(*i == 6);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 1);
			LIST<Aware<int> > l2;
			l1.splice(l1.begin(), l2);
			ASSERT(l1.size() == 1);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 1);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 1);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 1);
			LIST<Aware<int> > l2;
			l1.splice(l1.end(), l2);
			ASSERT(l1.size() == 1);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 1);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 1);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 1);
			LIST<Aware<int> > l2(a2, a2 + 1);
			l1.splice(l1.begin(), l2);
			ASSERT(l1.size() == 2);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 2);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 1);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 1);
			LIST<Aware<int> > l2(a2, a2 + 1);
			l1.splice(l1.end(), l2);
			ASSERT(l1.size() == 2);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 2);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 4);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 1);
			LIST<Aware<int> > l2(a2, a2 + 2);
			l1.splice(l1.begin(), l2);
			ASSERT(l1.size() == 3);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 3);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 5);
			++i;
			ASSERT(*i == 1);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 1);
			LIST<Aware<int> > l2(a2, a2 + 2);
			l1.splice(l1.end(), l2);
			ASSERT(l1.size() == 3);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 3);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 5);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 1);
			LIST<Aware<int> > l2(a2, a2 + 3);
			l1.splice(l1.begin(), l2);
			ASSERT(l1.size() == 4);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 4);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 5);
			++i;
			ASSERT(*i == 6);
			++i;
			ASSERT(*i == 1);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 1);
			LIST<Aware<int> > l2(a2, a2 + 3);
			l1.splice(l1.end(), l2);
			ASSERT(l1.size() == 4);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 4);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 5);
			++i;
			ASSERT(*i == 6);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 2);
			LIST<Aware<int> > l2;
			l1.splice(l1.begin(), l2);
			ASSERT(l1.size() == 2);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 2);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 2);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 2);
			LIST<Aware<int> > l2;
			l1.splice(NEXT(l1.begin()), l2);
			ASSERT(l1.size() == 2);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 2);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 2);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 2);
			LIST<Aware<int> > l2;
			l1.splice(NEXT(l1.begin(), 2), l2);
			ASSERT(l1.size() == 2);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 2);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 2);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 2);
			LIST<Aware<int> > l2(a2, a2 + 1);
			l1.splice(l1.begin(), l2);
			ASSERT(l1.size() == 3);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 3);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 2);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 2);
			LIST<Aware<int> > l2(a2, a2 + 1);
			l1.splice(NEXT(l1.begin()), l2);
			ASSERT(l1.size() == 3);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 3);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 2);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 2);
			LIST<Aware<int> > l2(a2, a2 + 1);
			l1.splice(NEXT(l1.begin(), 2), l2);
			ASSERT(l1.size() == 3);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 3);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 2);
			++i;
			ASSERT(*i == 4);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 2);
			LIST<Aware<int> > l2(a2, a2 + 2);
			l1.splice(l1.begin(), l2);
			ASSERT(l1.size() == 4);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 4);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 5);
			++i;
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 2);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 2);
			LIST<Aware<int> > l2(a2, a2 + 2);
			l1.splice(NEXT(l1.begin()), l2);
			ASSERT(l1.size() == 4);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 4);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 5);
			++i;
			ASSERT(*i == 2);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 2);
			LIST<Aware<int> > l2(a2, a2 + 2);
			l1.splice(NEXT(l1.begin(), 2), l2);
			ASSERT(l1.size() == 4);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 4);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 2);
			++i;
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 5);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 3);
			LIST<Aware<int> > l2(a2, a2 + 3);
			l1.splice(l1.begin(), l2);
			ASSERT(l1.size() == 6);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 6);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 5);
			++i;
			ASSERT(*i == 6);
			++i;
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 2);
			++i;
			ASSERT(*i == 3);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 3);
			LIST<Aware<int> > l2(a2, a2 + 3);
			l1.splice(NEXT(l1.begin()), l2);
			ASSERT(l1.size() == 6);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 6);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 5);
			++i;
			ASSERT(*i == 6);
			++i;
			ASSERT(*i == 2);
			++i;
			ASSERT(*i == 3);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 3);
			LIST<Aware<int> > l2(a2, a2 + 3);
			l1.splice(NEXT(l1.begin(), 2), l2);
			ASSERT(l1.size() == 6);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 6);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 2);
			++i;
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 5);
			++i;
			ASSERT(*i == 6);
			++i;
			ASSERT(*i == 3);
		}

		{
			LIST<Aware<int> > l1(a1, a1 + 3);
			LIST<Aware<int> > l2(a2, a2 + 3);
			l1.splice(NEXT(l1.begin(), 3), l2);
			ASSERT(l1.size() == 6);
			ASSERT(DISTANCE(l1.begin(), l1.end()) == 6);
			ASSERT(l2.size() == 0);
			ASSERT(DISTANCE(l2.begin(), l2.end()) == 0);
			LIST<Aware<int> >::const_iterator i = l1.begin();
			ASSERT(*i == 1);
			++i;
			ASSERT(*i == 2);
			++i;
			ASSERT(*i == 3);
			++i;
			ASSERT(*i == 4);
			++i;
			ASSERT(*i == 5);
			++i;
			ASSERT(*i == 6);
		}
	}

	ASSERT_AWARE_ZERO();

	return 0;
}
