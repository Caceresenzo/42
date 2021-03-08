/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_iter_size_value.pass.cpp                    :+:      :+:    :+:   */
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
		int a1[] = { 1, 2, 3 };
		int a2[] = { 1, 4, 4, 4, 4, 4, 2, 3 };

		LIST<Aware<int> > l1(a1, a1 + 3);
		l1.insert(NEXT(l1.begin()), 5, Aware<int>(4));
		ASSERT(l1 == LIST<Aware<int> >(a2, a2 + 8));
	}

	ASSERT_AWARE_ZERO();

	return (0);
}
