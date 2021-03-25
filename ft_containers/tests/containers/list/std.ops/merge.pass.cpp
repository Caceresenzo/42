/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.pass.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:35:33 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/09 15:35:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_list.hpp>

int
main()
{
	{
		int a1[] = { 1, 3, 7, 9, 10 };
		int a2[] = { 0, 2, 4, 5, 6, 8, 11 };
		int a3[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

		LIST<Aware<int> > c1(a1, a1 + sizeof(a1) / sizeof(a1[0]));
		LIST<Aware<int> > c2(a2, a2 + sizeof(a2) / sizeof(a2[0]));

		c1.merge(c2);
		ASSERT(c1 == LIST<Aware<int> >(a3, a3 + sizeof(a3) / sizeof(a3[0])));
		ASSERT(c2.empty());
	}

    {
    	int a1[] = { 1, 3, 7, 9, 10 };

		LIST<Aware<int> > c1(a1, a1 + sizeof(a1) / sizeof(a1[0]));

		c1.merge(c1);
		ASSERT((c1 == LIST<Aware<int> >(a1, a1 + sizeof(a1) / sizeof(a1[0]))));
	}
}
