/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal_range.pass.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 00:19:57 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/14 00:19:57 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_map.hpp>

int
main(void)
{

	typedef PAIR<const int, double> V;
	typedef MAP<int, double> M;

	{
		typedef PAIR<M::iterator, M::iterator> R;

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

		R r = m.equal_range(5);
		ASSERT(r.first == NEXT(m.begin(), 0));
		ASSERT(r.second == NEXT(m.begin(), 1));

		r = m.equal_range(7);
		ASSERT(r.first == NEXT(m.begin(), 1));
		ASSERT(r.second == NEXT(m.begin(), 2));

		r = m.equal_range(9);
		ASSERT(r.first == NEXT(m.begin(), 2));
		ASSERT(r.second == NEXT(m.begin(), 3));

		r = m.equal_range(11);
		ASSERT(r.first == NEXT(m.begin(), 3));
		ASSERT(r.second == NEXT(m.begin(), 4));

		r = m.equal_range(13);
		ASSERT(r.first == NEXT(m.begin(), 4));
		ASSERT(r.second == NEXT(m.begin(), 5));

		r = m.equal_range(15);
		ASSERT(r.first == NEXT(m.begin(), 5));
		ASSERT(r.second == NEXT(m.begin(), 6));

		r = m.equal_range(17);
		ASSERT(r.first == NEXT(m.begin(), 6));
		ASSERT(r.second == NEXT(m.begin(), 7));

		r = m.equal_range(19);
		ASSERT(r.first == NEXT(m.begin(), 7));
		ASSERT(r.second == NEXT(m.begin(), 8));

		r = m.equal_range(4);
		ASSERT(r.first == NEXT(m.begin(), 0));
		ASSERT(r.second == NEXT(m.begin(), 0));

		r = m.equal_range(6);
		ASSERT(r.first == NEXT(m.begin(), 1));
		ASSERT(r.second == NEXT(m.begin(), 1));

		r = m.equal_range(8);
		ASSERT(r.first == NEXT(m.begin(), 2));
		ASSERT(r.second == NEXT(m.begin(), 2));

		r = m.equal_range(10);
		ASSERT(r.first == NEXT(m.begin(), 3));
		ASSERT(r.second == NEXT(m.begin(), 3));

		r = m.equal_range(12);
		ASSERT(r.first == NEXT(m.begin(), 4));
		ASSERT(r.second == NEXT(m.begin(), 4));

		r = m.equal_range(14);
		ASSERT(r.first == NEXT(m.begin(), 5));
		ASSERT(r.second == NEXT(m.begin(), 5));

		r = m.equal_range(16);
		ASSERT(r.first == NEXT(m.begin(), 6));
		ASSERT(r.second == NEXT(m.begin(), 6));

		r = m.equal_range(18);
		ASSERT(r.first == NEXT(m.begin(), 7));
		ASSERT(r.second == NEXT(m.begin(), 7));

		r = m.equal_range(20);
		ASSERT(r.first == NEXT(m.begin(), 8));
		ASSERT(r.second == NEXT(m.begin(), 8));
	}

	{
		typedef PAIR<M::const_iterator, M::const_iterator> R;

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

		R r = m.equal_range(5);
		ASSERT(r.first == NEXT(m.begin(), 0));
		ASSERT(r.second == NEXT(m.begin(), 1));

		r = m.equal_range(7);
		ASSERT(r.first == NEXT(m.begin(), 1));
		ASSERT(r.second == NEXT(m.begin(), 2));

		r = m.equal_range(9);
		ASSERT(r.first == NEXT(m.begin(), 2));
		ASSERT(r.second == NEXT(m.begin(), 3));

		r = m.equal_range(11);
		ASSERT(r.first == NEXT(m.begin(), 3));
		ASSERT(r.second == NEXT(m.begin(), 4));

		r = m.equal_range(13);
		ASSERT(r.first == NEXT(m.begin(), 4));
		ASSERT(r.second == NEXT(m.begin(), 5));

		r = m.equal_range(15);
		ASSERT(r.first == NEXT(m.begin(), 5));
		ASSERT(r.second == NEXT(m.begin(), 6));

		r = m.equal_range(17);
		ASSERT(r.first == NEXT(m.begin(), 6));
		ASSERT(r.second == NEXT(m.begin(), 7));

		r = m.equal_range(19);
		ASSERT(r.first == NEXT(m.begin(), 7));
		ASSERT(r.second == NEXT(m.begin(), 8));

		r = m.equal_range(4);
		ASSERT(r.first == NEXT(m.begin(), 0));
		ASSERT(r.second == NEXT(m.begin(), 0));

		r = m.equal_range(6);
		ASSERT(r.first == NEXT(m.begin(), 1));
		ASSERT(r.second == NEXT(m.begin(), 1));

		r = m.equal_range(8);
		ASSERT(r.first == NEXT(m.begin(), 2));
		ASSERT(r.second == NEXT(m.begin(), 2));

		r = m.equal_range(10);
		ASSERT(r.first == NEXT(m.begin(), 3));
		ASSERT(r.second == NEXT(m.begin(), 3));

		r = m.equal_range(12);
		ASSERT(r.first == NEXT(m.begin(), 4));
		ASSERT(r.second == NEXT(m.begin(), 4));

		r = m.equal_range(14);
		ASSERT(r.first == NEXT(m.begin(), 5));
		ASSERT(r.second == NEXT(m.begin(), 5));

		r = m.equal_range(16);
		ASSERT(r.first == NEXT(m.begin(), 6));
		ASSERT(r.second == NEXT(m.begin(), 6));

		r = m.equal_range(18);
		ASSERT(r.first == NEXT(m.begin(), 7));
		ASSERT(r.second == NEXT(m.begin(), 7));

		r = m.equal_range(20);
		ASSERT(r.first == NEXT(m.begin(), 8));
		ASSERT(r.second == NEXT(m.begin(), 8));
	}
}
