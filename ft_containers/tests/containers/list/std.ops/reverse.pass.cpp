/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.pass.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:36:28 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/08 22:36:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_list.hpp>

int
main(void)
{
	{
		int a1[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
		int a2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

		LIST<Aware<int> > c1(a1, a1 + sizeof(a1) / sizeof(a1[0]));

		c1.reverse();
		ASSERT(c1 == LIST<Aware<int> >(a2, a2 + sizeof(a2) / sizeof(a2[0])));
	}

	ASSERT_AWARE_ZERO();
}
