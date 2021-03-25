/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_if.pass.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:58:02 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/08 21:58:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <counting_predicates.hpp>
#include <List.hpp>
#include <stddef.h>
#include <test_macros.hpp>
#include <unit_list.hpp>

bool
even(Aware<int> i)
{
	return (i.x() % 2 == 0);
}

bool
g(Aware<int> i)
{
	return (i.x() < 3);
}

typedef delegated_unary_counting_predicate<bool(*)(Aware<int> ), Aware<int> > Predicate;

int
main(void)
{
    {
		Aware<int> a1[] = { 1, 2, 3, 4 };
		Aware<int> a2[] = { 3, 4 };

		LIST<Aware<int> > c(a1, a1 + 4);

		unsigned long count = 0;
		Predicate dcp(g, &count);

		c.remove_if(dcp);
		ASSERT(c == LIST<Aware<int> >(a2, a2 + 2));
		ASSERT(dcp.count() == 4);
	}

    ASSERT_AWARE_ZERO();

	{
		Aware<int> a1[] = { 1, 2, 3, 4 };
		Aware<int> a2[] = { 1, 3 };

		LIST<Aware<int> > c(a1, a1 + 4);

		unsigned long count = 0;
		Predicate dcp(even, &count);

		c.remove_if(dcp);
		ASSERT(c == LIST<Aware<int> >(a2, a2 + 2));
		ASSERT(dcp.count() == 4);
	}

    ASSERT_AWARE_ZERO();
}
