/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_libft_str.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:29:42 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/05 01:29:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libs/ft.hpp>
#include <tests/test_unit.hpp>

CASE("libft", "strlen")
{
	ASSERT(ft::strlen(NULL) == 0);
	ASSERT(ft::strlen("") == 0);
	ASSERT(ft::strlen("Hello") == 5);

	return (0);
}
