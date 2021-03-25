/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back.pass.cpp                                 :+:      :+:    :+:   */
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
		LIST<Aware<int> > c;
		for (int i = 0; i < 5; ++i)
			c.push_back(i);

		Aware<int> a[] = { 0, 1, 2, 3, 4 };
		ASSERT(c == LIST<Aware<int> >(a, a + 5));
	}

	ASSERT_AWARE_ZERO();

	return (0);
}
