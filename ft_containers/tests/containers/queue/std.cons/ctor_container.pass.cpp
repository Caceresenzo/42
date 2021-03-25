/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_container.pass.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:58:14 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/10 14:58:14 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_queue.hpp>
#include <unit_list.hpp>

template<class C>
	C
	make(int n)
	{
		C c;
		for (int i = 0; i < n; ++i)
			c.push_back(i);

		return (c);
	}

template<class C>
	typename C::value_type
	at(const C &c, int n)
	{
		typedef typename C::const_iterator iterator;

		iterator it = c.begin();
		while (n--)
			it++;

		return (*it);
	}

int
main(void)
{
	{
		LIST<int> list = make<LIST<int> >(5);
		QUEUE<int, LIST<int> > queue(list);

		ASSERT(queue.size() == 5);
		for (std::size_t i = 0; i < list.size(); ++i)
		{
			ASSERT(queue.front() == at(list, i));
			queue.pop();
		}
	}

	ASSERT_AWARE_ZERO();
}
