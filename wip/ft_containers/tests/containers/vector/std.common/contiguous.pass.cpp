/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contiguous.pass.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 14:32:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/09/01 14:32:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_vector.hpp>

template<class C>
	void
	test_contiguous(const C &c)
	{
		for (size_t i = 0; i < c.size(); ++i)
			ASSERT(*(c.begin() + static_cast<typename C::difference_type>(i)) == *(addressof(*c.begin()) + i));
	}

int
main(void)
{
	TEST_AWARE_BLOCK({
		typedef Aware<int> T;
		typedef VECTOR<T> C;

		test_contiguous(C());
		test_contiguous(C(3, T(5)));
	});

	return (0);
}
