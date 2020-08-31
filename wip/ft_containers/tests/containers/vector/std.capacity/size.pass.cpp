/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:20:42 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 18:20:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Vector.hpp>
#include <test_macros.hpp>

int
main(void)
{
	TEST_AWARE_BLOCK({
		typedef ft::Vector<int> C;
		C c;

		ASSERT_NOEXCEPT(c.size());

		ASSERT(c.size() == 0);

		c.push_back(C::value_type(2));
		ASSERT(c.size() == 1);

		c.push_back(C::value_type(1));
		ASSERT(c.size() == 2);

		c.push_back(C::value_type(3));
		ASSERT(c.size() == 3);

		c.erase(c.begin());
		ASSERT(c.size() == 2);

		c.erase(c.begin());
		ASSERT(c.size() == 1);

		c.erase(c.begin());
		ASSERT(c.size() == 0);
	});

	return (0);
}
