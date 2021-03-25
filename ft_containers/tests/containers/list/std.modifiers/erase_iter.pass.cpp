/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.pass.cpp                                     :+:      :+:    :+:   */
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
		int a1[] = { 1, 2, 3 };
		LIST<int> l1(a1, a1 + 3);
		LIST<int>::iterator i = l1.begin();
		++i;

		LIST<int>::iterator j = l1.erase(i);
		ASSERT(l1.size() == 2);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 2);
		ASSERT(*j == 3);
		ASSERT(*l1.begin() == 1);
		ASSERT(*ft::next(l1.begin()) == 3);

		j = l1.erase(j);
		ASSERT(j == l1.end());
		ASSERT(l1.size() == 1);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 1);
		ASSERT(*l1.begin() == 1);

		j = l1.erase(l1.begin());
		ASSERT(j == l1.end());
		ASSERT(l1.size() == 0);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 0);
	}

	ASSERT_AWARE_ZERO();

	return (0);
}
