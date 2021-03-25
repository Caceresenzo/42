/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_front_rvalue.pass.cpp                          :+:      :+:    :+:   */
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
		LIST<Aware<int> > l1;

		l1.push_back(Aware<int>(1));
		ASSERT(l1.size() == 1);
		ASSERT(l1.front() == Aware<int>(1));

		l1.push_back(Aware<int>(2));
		ASSERT(l1.size() == 2);
		ASSERT(l1.front() == Aware<int>(1));
		ASSERT(l1.back() == Aware<int>(2));
	}

	ASSERT_AWARE_ZERO();

	return 0;
}
