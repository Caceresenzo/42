/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:23:59 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 18:23:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test_macros.hpp>
#include <Vector.hpp>

int
main(void)
{
	TEST_AWARE_BLOCK({
		ft::Vector<Aware<int> > v1(100);
		ft::Vector<Aware<int> > v2(200);

		v1.swap(v2);
		ASSERT(v1.size() == 200);
		ASSERT(v1.capacity() == 200);
		ASSERT(v2.size() == 100);
		ASSERT(v2.capacity() == 100);
	});

	return (0);
}
