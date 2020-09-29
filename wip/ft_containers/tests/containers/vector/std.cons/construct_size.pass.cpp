/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_size.pass.cpp                            :+:      :+:    :+:   */
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
	test(typename C::size_type n)
	{
		C c(n);

		ASSERT(c.size() == n);
	}

int
main(int, char**)
{
	test<VECTOR<int> >(50);
	test<VECTOR<Aware<int> > >(500);

	ASSERT_AWARE_ZERO();

	return (0);
}
