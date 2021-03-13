/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_cv.pass.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 23:26:26 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/13 23:26:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_map.hpp>

int
main(void)
{
	{
		typedef MAP<int, double> M;
		typedef PAIR<M::iterator, bool> R;
		typedef M::value_type VT;
		M m;

		const VT v1(2, 2.5);
		R r = m.insert(v1);
		ASSERT(r.second);
		ASSERT(r.first == m.begin());
		ASSERT(m.size() == 1);
		ASSERT(r.first->first == 2);
		ASSERT(r.first->second == 2.5);

		const VT v2(1, 1.5);
		r = m.insert(v2);
		ASSERT(r.second);
		ASSERT(r.first == m.begin());
		ASSERT(m.size() == 2);
		ASSERT(r.first->first == 1);
		ASSERT(r.first->second == 1.5);

		const VT v3(3, 3.5);
		r = m.insert(v3);
		ASSERT(r.second);
		ASSERT(r.first == PREV(m.end()));
		ASSERT(m.size() == 3);
		ASSERT(r.first->first == 3);
		ASSERT(r.first->second == 3.5);

		const VT v4(3, 4.5);
		r = m.insert(v4);
		ASSERT(!r.second);
		ASSERT(r.first == PREV(m.end()));
		ASSERT(m.size() == 3);
		ASSERT(r.first->first == 3);
		ASSERT(r.first->second == 3.5);
	}
}
