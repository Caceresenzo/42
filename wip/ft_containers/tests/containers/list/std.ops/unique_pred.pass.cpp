/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique.pass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:43:41 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/08 22:43:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_list.hpp>

bool g(Aware<int> x, Aware<int> y)
{
    return (x == y);
}

int
main(void)
{
    {
		int a1[] = { 2, 1, 1, 4, 4, 4, 4, 3, 3 };
		int a2[] = { 2, 1, 4, 3 };

		LIST<Aware<int> > c(a1, a1 + sizeof(a1) / sizeof(a1[0]));

		c.unique(g);
		ASSERT(c == LIST<Aware<int> >(a2, a2 + sizeof(a2) / sizeof(a2[0])));
	}

	ASSERT_AWARE_ZERO();
}
