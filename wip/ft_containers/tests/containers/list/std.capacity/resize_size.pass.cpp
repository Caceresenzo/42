/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_size.pass.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:26:52 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/08 13:26:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_list.hpp>

int
main(void)
{
	TEST_AWARE_BLOCK({
		typedef LIST<Aware<int> > C;
		C l(5, Aware<int>(2));

        l.resize(2);
        ASSERT(l.size() == 2);
        ASSERT(DISTANCE(l.begin(), l.end()) == 2);
        ASSERT(l == C(2, Aware<int>(2)));
	});

	TEST_AWARE_BLOCK({
		typedef LIST<Aware<int> > C;
		C l(5, Aware<int>(2));

        l.resize(10);
        ASSERT(l.size() == 10);
        ASSERT(DISTANCE(l.begin(), l.end()) == 10);
        ASSERT(l.front() == Aware<int>(2));
        ASSERT(l.back() == Aware<int>(0));
	});

	return (0);
}
