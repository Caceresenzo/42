/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_libft_to.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:29:42 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/05 01:29:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libs/ft.hpp>
#include <tests/test_unit.hpp>

CASE("libft", "tolower")
{
	ASSERT(ft::tolower('a') == 'a');
	ASSERT(ft::tolower('z') == 'z');

	ASSERT(ft::tolower('A') == 'a');
	ASSERT(ft::tolower('Z') == 'z');

	return (0);
}

CASE("libft", "toupper")
{
	ASSERT(ft::toupper('A') == 'A');
	ASSERT(ft::toupper('Z') == 'Z');

	ASSERT(ft::toupper('a') == 'A');
	ASSERT(ft::toupper('z') == 'Z');

	return (0);
}
