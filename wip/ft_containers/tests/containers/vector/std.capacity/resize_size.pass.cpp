/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_size.pass.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:37:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 17:37:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_vector.hpp>

int
main(void)
{
	TEST_AWARE_BLOCK({
		VECTOR<Aware<int> > v(100);

		v.resize(50);
		ASSERT(v.size() == 50);
		ASSERT(v.capacity() == 100);

		v.resize(200);
		ASSERT(v.size() == 200);
		ASSERT(v.capacity() >= 200);
	});

	return (0);
}
