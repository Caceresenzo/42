/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_back.pass.cpp                                  :+:      :+:    :+:   */
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
		Aware<int> a[] = { 1, 2, 3 };
		LIST<Aware<int> > c(a, a + 3);

		c.pop_back();
		ASSERT(c == LIST<Aware<int> >(a, a + 2));

		c.pop_back();
		ASSERT(c == LIST<Aware<int> >(a, a + 1));

		c.pop_back();
		ASSERT(c.empty());
	}

	ASSERT_AWARE_ZERO();

	return (0);
}
