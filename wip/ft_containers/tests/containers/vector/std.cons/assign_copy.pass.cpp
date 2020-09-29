/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_copy.pass.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:20:42 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 18:20:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_vector.hpp>

int
main(void)
{
	TEST_AWARE_BLOCK({
		VECTOR<Aware<int> > l(3, Aware<int>(2));
		VECTOR<Aware<int> > l2(l);

		l2 = l;

		ASSERT(l2 == l);
	});

	TEST_AWARE_BLOCK({
		VECTOR<Aware<int> > l(3, Aware<int>(2));
		VECTOR<Aware<int> > l2(l);

		l2 = l;

		ASSERT(l2 == l);
	});

	return (0);
}
