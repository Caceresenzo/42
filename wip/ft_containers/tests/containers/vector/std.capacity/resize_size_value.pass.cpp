/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_size_value.pass.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:16:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 18:16:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_vector.hpp>

int
main(void)
{
	TEST_AWARE_BLOCK({
		VECTOR<Aware<int> > v(100);

		v.resize(50, 1);
		ASSERT(v.size() == 50);
		ASSERT(v.capacity() == 100);
		ASSERT(v == VECTOR<Aware<int> >(50));

		v.resize(200, 1);
		ASSERT(v.size() == 200);
		ASSERT(v.capacity() >= 200);

		for (unsigned i = 0; i < 50; ++i)
			ASSERT(v[i] == 0);

		for (unsigned i = 50; i < 200; ++i)
			ASSERT(v[i] == 1);
	});

	return (0);
}
