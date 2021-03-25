/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.pass.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 20:15:18 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/13 20:15:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_map.hpp>

int
main(void)
{
	{
		typedef PAIR<const int, double> V;
		typedef MAP<int, double> M;
		typedef M::size_type R;

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

		R r = m.count(5);
		ASSERT(r == 1);

		r = m.count(6);
		ASSERT(r == 1);

		r = m.count(7);
		ASSERT(r == 1);

		r = m.count(8);
		ASSERT(r == 1);

		r = m.count(9);
		ASSERT(r == 1);

		r = m.count(10);
		ASSERT(r == 1);

		r = m.count(11);
		ASSERT(r == 1);

		r = m.count(12);
		ASSERT(r == 1);

		r = m.count(4);
		ASSERT(r == 0);
	}
}
