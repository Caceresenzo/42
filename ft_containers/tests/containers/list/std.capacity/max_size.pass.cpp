/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_size.pass.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 13:20:24 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/08 13:20:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits>

#include <unit_list.hpp>

int
main(int, char**)
{
	{
		typedef LIST<char> C;
		const C::size_type max_dist = static_cast<C::size_type>(std::numeric_limits<C::difference_type>::max());
		C c;
		ASSERT(c.max_size() <= max_dist);
	}

	{
		typedef LIST<Aware<long> > C;
		const C::size_type max_dist = static_cast<C::size_type>(std::numeric_limits<C::difference_type>::max());
		C c;
		ASSERT(c.max_size() <= max_dist);
	}

	return 0;
}
