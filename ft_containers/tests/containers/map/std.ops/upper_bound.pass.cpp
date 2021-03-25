/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upper_bound.pass.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 00:15:48 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/14 00:15:48 by ecaceres         ###   ########.fr       */
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
			V(7, 6),
			V(9, 7),
			V(11, 8),
			V(13, 9),
			V(15, 10),
			V(17, 11),
			V(19, 12) };

		M m(ar, ar + sizeof(ar) / sizeof(ar[0]));

		R r = m.upper_bound(5);
		ASSERT(r == NEXT(m.begin(), 1));

		r = m.upper_bound(7);
		ASSERT(r == NEXT(m.begin(), 2));

		r = m.upper_bound(9);
		ASSERT(r == NEXT(m.begin(), 3));

		r = m.upper_bound(11);
		ASSERT(r == NEXT(m.begin(), 4));

		r = m.upper_bound(13);
		ASSERT(r == NEXT(m.begin(), 5));

		r = m.upper_bound(15);
		ASSERT(r == NEXT(m.begin(), 6));

		r = m.upper_bound(17);
		ASSERT(r == NEXT(m.begin(), 7));

		r = m.upper_bound(19);
		ASSERT(r == NEXT(m.begin(), 8));

		r = m.upper_bound(4);
		ASSERT(r == NEXT(m.begin(), 0));

		r = m.upper_bound(6);
		ASSERT(r == NEXT(m.begin(), 1));

		r = m.upper_bound(8);
		ASSERT(r == NEXT(m.begin(), 2));

		r = m.upper_bound(10);
		ASSERT(r == NEXT(m.begin(), 3));

		r = m.upper_bound(12);
		ASSERT(r == NEXT(m.begin(), 4));

		r = m.upper_bound(14);
		ASSERT(r == NEXT(m.begin(), 5));

		r = m.upper_bound(16);
		ASSERT(r == NEXT(m.begin(), 6));

		r = m.upper_bound(18);
		ASSERT(r == NEXT(m.begin(), 7));

		r = m.upper_bound(20);
		ASSERT(r == NEXT(m.begin(), 8));
	}

	{
		typedef M::const_iterator R;

		V ar[] = {
			V(5, 5),
			V(7, 6),
			V(9, 7),
			V(11, 8),
			V(13, 9),
			V(15, 10),
			V(17, 11),
			V(19, 12) };

		const M m(ar, ar + sizeof(ar) / sizeof(ar[0]));

		R r = m.upper_bound(5);
		ASSERT(r == NEXT(m.begin(), 1));

		r = m.upper_bound(7);
		ASSERT(r == NEXT(m.begin(), 2));

		r = m.upper_bound(9);
		ASSERT(r == NEXT(m.begin(), 3));

		r = m.upper_bound(11);
		ASSERT(r == NEXT(m.begin(), 4));

		r = m.upper_bound(13);
		ASSERT(r == NEXT(m.begin(), 5));

		r = m.upper_bound(15);
		ASSERT(r == NEXT(m.begin(), 6));

		r = m.upper_bound(17);
		ASSERT(r == NEXT(m.begin(), 7));

		r = m.upper_bound(19);
		ASSERT(r == NEXT(m.begin(), 8));

		r = m.upper_bound(4);
		ASSERT(r == NEXT(m.begin(), 0));

		r = m.upper_bound(6);
		ASSERT(r == NEXT(m.begin(), 1));

		r = m.upper_bound(8);
		ASSERT(r == NEXT(m.begin(), 2));

		r = m.upper_bound(10);
		ASSERT(r == NEXT(m.begin(), 3));

		r = m.upper_bound(12);
		ASSERT(r == NEXT(m.begin(), 4));

		r = m.upper_bound(14);
		ASSERT(r == NEXT(m.begin(), 5));

		r = m.upper_bound(16);
		ASSERT(r == NEXT(m.begin(), 6));

		r = m.upper_bound(18);
		ASSERT(r == NEXT(m.begin(), 7));

		r = m.upper_bound(20);
		ASSERT(r == NEXT(m.begin(), 8));
	}
}
