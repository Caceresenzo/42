/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_size.pass.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:37:11 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/13 14:37:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_map.hpp>
#include <limits>

int
main(void)
{
	{
		typedef MAP<char, int> C;
		const C::size_type max_dist = static_cast<C::size_type>(std::numeric_limits<C::difference_type>::max());
		C c;

		ASSERT(c.max_size() <= max_dist);
	}
}
