/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_iter_iter.pass.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 23:32:11 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/13 23:32:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_map.hpp>

int
main(void)
{
	{
		typedef MAP<int, double> M;
		typedef PAIR<int, double> P;

		P ar[] = {
			P(1, 1),
			P(1, 1.5),
			P(1, 2),
			P(2, 1),
			P(2, 1.5),
			P(2, 2),
			P(3, 1),
			P(3, 1.5),
			P(3, 2), };

		M m;

		m.insert(ar, ar + sizeof(ar) / sizeof(ar[0]));
		ASSERT(m.size() == 3);
		ASSERT(m.begin()->first == 1);
		ASSERT(m.begin()->second == 1);
		ASSERT(NEXT(m.begin())->first == 2);
		ASSERT(NEXT(m.begin())->second == 1);
		ASSERT(NEXT(m.begin(), 2)->first == 3);
		ASSERT(NEXT(m.begin(), 2)->second == 1);
	}
}
