/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_iter_iter_iter.pass.cpp                     :+:      :+:    :+:   */
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
	    LIST<Aware<int> > l1;
	    typedef LIST<Aware<int> >::iterator iterator;

		Aware<int> a1[] = { 1, 2, 3 };
		/* iterator i = */ l1.insert(l1.begin(), a1, a1 + 3);
		iterator i = l1.begin();

	    ASSERT(i == l1.begin());
	    ASSERT(l1.size() == 3);
	    ASSERT(DISTANCE(l1.begin(), l1.end()) == 3);

	    i = l1.begin();
	    ASSERT(*i == 1);

	    ++i;
	    ASSERT(*i == 2);

	    ++i;
	    ASSERT(*i == 3);

	    Aware<int> a2[] = { 4, 5, 6 };
	    /* i = */ l1.insert(i, a2, a2 + 3);
	    ASSERT(l1.size() == 6);
	    ASSERT(DISTANCE(l1.begin(), l1.end()) == 6);

	    i = l1.begin();
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

	ASSERT_AWARE_ZERO();

	return (0);
}
