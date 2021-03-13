/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.pass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 19:45:09 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/13 19:45:09 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_map.hpp>

int
main(void)
{
	{
		typedef MAP<Aware<int>, Aware<double> > M;
		M m;

		ASSERT(m.size() == 0);

		m.insert(M::value_type(2, 1.5));
		ASSERT(m.size() == 1);

		m.insert(M::value_type(1, 1.5));
		ASSERT(m.size() == 2);

		m.insert(M::value_type(3, 1.5));
		ASSERT(m.size() == 3);

		m.erase(m.begin());
		ASSERT(m.size() == 2);

		m.erase(m.begin());
		ASSERT(m.size() == 1);

		m.erase(m.begin());
		ASSERT(m.size() == 0);
	}

	ASSERT_AWARE_ZERO();
}
