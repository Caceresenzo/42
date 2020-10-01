/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_iter_iter.pass.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 20:09:07 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 20:09:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_vector.hpp>

int
main(void)
{
	TEST_AWARE_BLOCK({
		VECTOR<Aware<int> > l1;
		l1.push_back(1);
		l1.push_back(2);
		l1.push_back(3);

		VECTOR<Aware<int> >::iterator i = l1.erase(l1.begin(), l1.begin());
		ASSERT(l1.size() == 3);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 3);
		ASSERT(i == l1.begin());
	});

	TEST_AWARE_BLOCK({
		VECTOR<Aware<int> > l1;
		l1.push_back(1);
		l1.push_back(2);
		l1.push_back(3);

		VECTOR<Aware<int> > l2;
		l2.push_back(2);
		l2.push_back(3);

		VECTOR<Aware<int> >::iterator i = l1.erase(l1.begin(), l1.begin() + 1);
		ASSERT(l1.size() == 2);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 2);
		ASSERT(i == l1.begin());
		ASSERT(l1 == l2);
	});

	TEST_AWARE_BLOCK({
		VECTOR<Aware<int> > l1;
		l1.push_back(1);
		l1.push_back(2);
		l1.push_back(3);

		VECTOR<Aware<int> > l2;
		l2.push_back(3);

		VECTOR<Aware<int> >::iterator i = l1.erase(l1.begin(), l1.begin() + 2);
		ASSERT(l1.size() == 1);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 1);
		ASSERT(i == l1.begin());
		ASSERT(l1 == l2);
	});

	TEST_AWARE_BLOCK({
		VECTOR<Aware<int> > l1;
		l1.push_back(1);
		l1.push_back(2);
		l1.push_back(3);


		VECTOR<Aware<int> >::iterator i = l1.erase(l1.begin(), l1.begin() + 3);
		ASSERT(l1.size() == 0);
		ASSERT(DISTANCE(l1.begin(), l1.end()) == 0);
		ASSERT(i == l1.begin());
	});

	TEST_AWARE_BLOCK({
		VECTOR<VECTOR<Aware<int> > > outer(2, VECTOR<Aware<int> >(1));

		outer.erase(outer.begin(), outer.begin());
		ASSERT(outer.size() == 2);
		ASSERT(outer[0].size() == 1);
		ASSERT(outer[1].size() == 1);
	});

	return (0);
}
