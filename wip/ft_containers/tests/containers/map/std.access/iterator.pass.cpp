/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.pass.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 20:09:49 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/13 20:09:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_map.hpp>

int
main(void)
{
	{
		typedef PAIR<const int, Aware<double> > V;
		V ar[] = {
			V(1, 1),
			V(1, 1.5),
			V(1, 2),
			V(2, 1),
			V(2, 1.5),
			V(2, 2),
			V(3, 1),
			V(3, 1.5),
			V(3, 2),
			V(4, 1),
			V(4, 1.5),
			V(4, 2),
			V(5, 1),
			V(5, 1.5),
			V(5, 2),
			V(6, 1),
			V(6, 1.5),
			V(6, 2),
			V(7, 1),
			V(7, 1.5),
			V(7, 2),
			V(8, 1),
			V(8, 1.5),
			V(8, 2) };

		MAP<int, Aware<double> > m(ar, ar + sizeof(ar) / sizeof(ar[0]));

		ASSERT(static_cast<std::size_t>(DISTANCE(m.begin(), m.end())) == m.size());
		ASSERT(static_cast<std::size_t>(DISTANCE(m.rbegin(), m.rend())) == m.size());

		MAP<int, Aware<double> >::iterator i;
		i = m.begin();
		MAP<int, Aware<double> >::const_iterator k = i;
		ASSERT(i == k);

		for (int j = 1; static_cast<std::size_t>(j) <= m.size(); ++j, ++i)
		{
			ASSERT(i->first == j);
			ASSERT(i->second == 1);
			i->second = 2.5;
			ASSERT(i->second == 2.5);
		}
	}

	ASSERT_AWARE_ZERO();

	{
		typedef PAIR<const int, Aware<double> > V;
		V ar[] = {
			V(1, 1),
			V(1, 1.5),
			V(1, 2),
			V(2, 1),
			V(2, 1.5),
			V(2, 2),
			V(3, 1),
			V(3, 1.5),
			V(3, 2),
			V(4, 1),
			V(4, 1.5),
			V(4, 2),
			V(5, 1),
			V(5, 1.5),
			V(5, 2),
			V(6, 1),
			V(6, 1.5),
			V(6, 2),
			V(7, 1),
			V(7, 1.5),
			V(7, 2),
			V(8, 1),
			V(8, 1.5),
			V(8, 2) };

		const MAP<int, Aware<double> > m(ar, ar + sizeof(ar) / sizeof(ar[0]));

		ASSERT(static_cast<std::size_t>(DISTANCE(m.begin(), m.end())) == m.size());
		ASSERT(static_cast<std::size_t>(DISTANCE(m.rbegin(), m.rend())) == m.size());

		MAP<int, Aware<double> >::const_iterator i;
		i = m.begin();
		for (int j = 1; static_cast<std::size_t>(j) <= m.size(); ++j, ++i)
		{
			ASSERT(i->first == j);
			ASSERT(i->second == 1);
		}
	}

	ASSERT_AWARE_ZERO();
}
