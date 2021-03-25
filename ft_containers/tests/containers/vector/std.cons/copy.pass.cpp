/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.pass.cpp                                      :+:      :+:    :+:   */
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
		typedef VECTOR<Aware<int> > V;

		V v;
		for (int i = 0; i < 42; ++i) {
			v.push_back(i);
		}

		V::size_type s = v.size();

		V c(v);
		ASSERT(c.size() == s);
		ASSERT(c == v);
	});

	return (0);
}
