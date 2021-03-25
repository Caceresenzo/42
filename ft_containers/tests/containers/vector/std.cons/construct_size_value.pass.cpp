/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_size_value.pass.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:20:42 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 18:20:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_vector.hpp>

template<class C>
	void
	test(typename C::size_type n, const typename C::value_type &x)
	{
		C c(n, x);
		ASSERT(c.size() == n);

		for (typename C::const_iterator i = c.begin(), e = c.end(); i != e; ++i)
			ASSERT(*i == x);
	}

int
main(void)
{
	test<VECTOR<int> >(50, 3);
	test<VECTOR<Aware<int> > >(50, 5);

	ASSERT_AWARE_ZERO();

	return (0);
}
