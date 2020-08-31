/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_size_value.pass.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:20:42 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 18:20:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Vector.hpp>
#include <test_macros.hpp>

bool
is6(const Aware<int> &x)
{
	return (x == Aware<int>(6));
}

void
test(ft::Vector<Aware<int> > &v)
{
	v.assign(5, Aware<int>(6));
	ASSERT(v.size() == 5);

	for (ft::Vector<Aware<int> >::iterator it = v.begin(); it < v.end(); it++)
	{
		ASSERT(is6(*it));
	}
}

int
main(void)
{
	TEST_AWARE_BLOCK({
		typedef ft::Vector<Aware<int> > V;
		V d1;
		V d2;

		d2.reserve(10);

		test(d1);
		test(d2);
	});

	return (0);
}
