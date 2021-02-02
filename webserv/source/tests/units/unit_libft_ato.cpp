/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_libft_ato.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:29:42 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/05 01:29:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libs/ft.hpp>
#include <tests/test_unit.hpp>

CASE("libft", "atoi")
{
	ASSERT(ft::atoi("") == 0);
	ASSERT(ft::atoi("0") == 0);
	ASSERT(ft::atoi("1") == 1);
	ASSERT(ft::atoi("-1") == -1);
	ASSERT(ft::atoi("42") == 42);
	ASSERT(ft::atoi("-42") == -42);

	return (0);
}
