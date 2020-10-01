/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.pass.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:35:33 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 17:35:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_list.hpp>

int
main(void)
{
	{
		Aware<int> a[] = { 1, 2, 3 };
		LIST<Aware<int> > c(a, a + 3);

		c.clear();
		ASSERT(c.empty());
	}

	ASSERT_AWARE_ZERO();

	return (0);
}
