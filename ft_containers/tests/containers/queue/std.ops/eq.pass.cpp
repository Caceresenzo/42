/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eq.pass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:12:54 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/10 16:12:54 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_queue.hpp>

template<class C>
	C
	make(int n)
	{
		C c;

		for (int i = 0; i < n; ++i)
			c.push(i);

		return (c);
	}

int
main(void)
{
	QUEUE<int> q1 = make<QUEUE<int> >(5);
	QUEUE<int> q2 = make<QUEUE<int> >(10);
	QUEUE<int> q1_save = q1;
	QUEUE<int> q2_save = q2;

	ASSERT(q1 == q1_save);
	ASSERT(q1 != q2);
	ASSERT(q2 == q2_save);
}
