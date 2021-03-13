/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_iter.pass.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 22:51:22 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/13 22:51:22 by ecaceres         ###   ########.fr       */
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
			P(1, 1.5),
			P(2, 2.5),
			P(3, 3.5),
			P(4, 4.5),
			P(5, 5.5),
			P(6, 6.5),
			P(7, 7.5),
			P(8, 8.5), };

		M m(ar, ar + sizeof(ar) / sizeof(ar[0]));

		ASSERT(m.size() == 8);

		m.erase(m.begin(), m.begin());
		ASSERT(m.size() == 8);
		ASSERT(m.begin()->first == 1);
		ASSERT(m.begin()->second == 1.5);
		ASSERT(NEXT(m.begin())->first == 2);
		ASSERT(NEXT(m.begin())->second == 2.5);
		ASSERT(NEXT(m.begin(), 2)->first == 3);
		ASSERT(NEXT(m.begin(), 2)->second == 3.5);
		ASSERT(NEXT(m.begin(), 3)->first == 4);
		ASSERT(NEXT(m.begin(), 3)->second == 4.5);
		ASSERT(NEXT(m.begin(), 4)->first == 5);
		ASSERT(NEXT(m.begin(), 4)->second == 5.5);
		ASSERT(NEXT(m.begin(), 5)->first == 6);
		ASSERT(NEXT(m.begin(), 5)->second == 6.5);
		ASSERT(NEXT(m.begin(), 6)->first == 7);
		ASSERT(NEXT(m.begin(), 6)->second == 7.5);
		ASSERT(NEXT(m.begin(), 7)->first == 8);
		ASSERT(NEXT(m.begin(), 7)->second == 8.5);

		m.erase(m.begin(), NEXT(m.begin(), 2));
		ASSERT(m.size() == 6);
		ASSERT(NEXT(m.begin(), 0)->first == 3);
		ASSERT(NEXT(m.begin(), 0)->second == 3.5);
		ASSERT(NEXT(m.begin(), 1)->first == 4);
		ASSERT(NEXT(m.begin(), 1)->second == 4.5);
		ASSERT(NEXT(m.begin(), 2)->first == 5);
		ASSERT(NEXT(m.begin(), 2)->second == 5.5);
		ASSERT(NEXT(m.begin(), 3)->first == 6);
		ASSERT(NEXT(m.begin(), 3)->second == 6.5);
		ASSERT(NEXT(m.begin(), 4)->first == 7);
		ASSERT(NEXT(m.begin(), 4)->second == 7.5);
		ASSERT(NEXT(m.begin(), 5)->first == 8);
		ASSERT(NEXT(m.begin(), 5)->second == 8.5);

		m.erase(NEXT(m.begin(), 2), NEXT(m.begin(), 6));
		ASSERT(m.size() == 2);
		ASSERT(NEXT(m.begin(), 0)->first == 3);
		ASSERT(NEXT(m.begin(), 0)->second == 3.5);
		ASSERT(NEXT(m.begin(), 1)->first == 4);
		ASSERT(NEXT(m.begin(), 1)->second == 4.5);

		m.erase(m.begin(), m.end());
		ASSERT(m.size() == 0);
		ASSERT(m.begin() == m.end());
	}
}
