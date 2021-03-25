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

#include <unit_stack.hpp>
#include <unit_vector.hpp>

template<class C>
	C
	make(int n)
	{
		C c;
		for (int i = 0; i < n; ++i)
			c.push_back(i);

		return (c);
	}

int
main(void)
{
	{
		VECTOR<int> vector = make<VECTOR<int> >(5);
		STACK<int, VECTOR<int> > stack(vector);

		ASSERT(stack.size() == 5);
		for (std::size_t i = 0; i < vector.size(); ++i)
		{
			ASSERT(stack.top() == vector[vector.size() - i - 1]);
			stack.pop();
		}
	}

	ASSERT_AWARE_ZERO();
}
