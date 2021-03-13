/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.pass.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 20:13:03 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/13 20:13:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_map.hpp>

int
main(void)
{
	{
		typedef MAP<Aware<int>, Aware<double> > M;
		typedef PAIR<Aware<int>, Aware<double> > P;
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
		ASSERT_NOEXCEPT(m.clear());

		m.clear();
		ASSERT(m.size() == 0);
	}

	ASSERT_AWARE_ZERO();
}
