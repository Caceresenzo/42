/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.pass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 20:19:58 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/13 20:19:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_map.hpp>

int
main(void)
{
	typedef PAIR<const int, double> V;
	typedef MAP<int, double> M;

	{
		typedef M::iterator R;

		V ar[] = {
			V(5, 5),
			V(6, 6),
			V(7, 7),
			V(8, 8),
			V(9, 9),
			V(10, 10),
			V(11, 11),
			V(12, 12) };

		M m(ar, ar + sizeof(ar) / sizeof(ar[0]));

		R r = m.find(5);
		ASSERT(r == m.begin());

		r = m.find(6);
		ASSERT(r == NEXT(m.begin()));

		r = m.find(7);
		ASSERT(r == NEXT(m.begin(), 2));

		r = m.find(8);
		ASSERT(r == NEXT(m.begin(), 3));

		r = m.find(9);
		ASSERT(r == NEXT(m.begin(), 4));

		r = m.find(10);
		ASSERT(r == NEXT(m.begin(), 5));

		r = m.find(11);
		ASSERT(r == NEXT(m.begin(), 6));

		r = m.find(12);
		ASSERT(r == NEXT(m.begin(), 7));

		r = m.find(4);
		ASSERT(r == NEXT(m.begin(), 8));
	}

	{
		typedef M::const_iterator R;

		V ar[] = {
			V(5, 5),
			V(6, 6),
			V(7, 7),
			V(8, 8),
			V(9, 9),
			V(10, 10),
			V(11, 11),
			V(12, 12) };

		const M m(ar, ar + sizeof(ar) / sizeof(ar[0]));

		R r = m.find(5);
		ASSERT(r == m.begin());

		r = m.find(6);
		ASSERT(r == NEXT(m.begin()));

		r = m.find(7);
		ASSERT(r == NEXT(m.begin(), 2));

		r = m.find(8);
		ASSERT(r == NEXT(m.begin(), 3));

		r = m.find(9);
		ASSERT(r == NEXT(m.begin(), 4));

		r = m.find(10);
		ASSERT(r == NEXT(m.begin(), 5));

		r = m.find(11);
		ASSERT(r == NEXT(m.begin(), 6));

		r = m.find(12);
		ASSERT(r == NEXT(m.begin(), 7));

		r = m.find(4);
		ASSERT(r == NEXT(m.begin(), 8));
	}
}
