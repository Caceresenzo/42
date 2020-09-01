/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.pass.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 13:54:06 by ecaceres          #+#    #+#             */
/*   Updated: 2020/09/01 13:54:06 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Vector.hpp>
#include <test_macros.hpp>

int
main(void)
{
	{
		Aware<int> a[] = { 1, 2, 3 };

		ft::Vector<Aware<int> > c(a, a + 3);

		c.clear();
		ASSERT(c.empty());
	}

	ASSERT_AWARE_ZERO();

	return (0);
}
