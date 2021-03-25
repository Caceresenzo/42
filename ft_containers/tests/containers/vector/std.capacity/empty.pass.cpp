/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty.pass.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:12:35 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 17:12:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_vector.hpp>

int
main(void)
{
	TEST_AWARE_BLOCK({
		typedef VECTOR<Aware<int> > C;
		C c;

		ASSERT_NOEXCEPT(c.empty());

		ASSERT(c.empty());

		c.push_back(C::value_type(1));
		ASSERT(!c.empty());

		c.clear();
		ASSERT(c.empty());
	});

	return (0);
}
