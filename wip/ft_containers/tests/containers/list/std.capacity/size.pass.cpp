/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.pass.cpp                                      :+:      :+:    :+:   */
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
	TEST_AWARE_BLOCK({
		typedef LIST<Aware<int> > C;
		C c;

		ASSERT(c.size() == 0);

		c.push_back(2);
		ASSERT(c.size() == 1);

		c.push_back(1);
		ASSERT(c.size() == 2);

		c.push_back(3);
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
