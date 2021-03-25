/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_back.pass.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 13:54:06 by ecaceres          #+#    #+#             */
/*   Updated: 2020/09/01 13:54:06 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_vector.hpp>

int
main(void)
{
	TEST_AWARE_BLOCK({
		VECTOR<Aware<int> > c;

		c.push_back(1);
		ASSERT(c.size() == 1);

		c.pop_back();
		ASSERT(c.size() == 0);
	});

	{
		Aware<int> arr[] = { 0, 1, 2, 3, 4 };
		int sz = 5;
		VECTOR<Aware<int> > c(arr, arr + sz);

		while (c.size() < c.capacity())
			c.push_back(sz++);

		c.push_back(c.front());
		ASSERT(c.back() == 0);

		for (int i = 0; i < sz; ++i)
			ASSERT(c[i] == i);
	}

	ASSERT_AWARE_ZERO();

	return (0);
}
