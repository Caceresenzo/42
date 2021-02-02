/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_libft_is.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:29:42 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/05 01:29:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libs/ft.hpp>
#include <tests/test_unit.hpp>

CASE("libft", "islower")
{
	ASSERT(ft::islower('a'));
	ASSERT(ft::islower('z'));

	ASSERT(!ft::islower('A'));
	ASSERT(!ft::islower('Z'));

	return (0);
}

CASE("libft", "isupper")
{
	ASSERT(ft::isupper('A'));
	ASSERT(ft::isupper('Z'));

	ASSERT(!ft::isupper('a'));
	ASSERT(!ft::isupper('z'));

	return (0);
}
