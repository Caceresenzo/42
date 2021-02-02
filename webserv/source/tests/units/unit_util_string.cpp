/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_util_string.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 00:54:37 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/26 00:54:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests/test_unit.hpp>
#include <util/StringUtils.hpp>
#include <string>

CASE("string-util", "toUpperCase")
{
	ASSERT(StringUtils::toUpperCase("Hello") == "HELLO");

	return (0);
}

CASE("string-util", "equalsIgnoreCase")
{
	ASSERT(StringUtils::equalsIgnoreCase("Hello", "Hello"));
	ASSERT(StringUtils::equalsIgnoreCase("HELLO", "Hello"));
	ASSERT(StringUtils::equalsIgnoreCase("Hello", "HELLO"));
	ASSERT(StringUtils::equalsIgnoreCase("hello", "Hello"));
	ASSERT(StringUtils::equalsIgnoreCase("Hello", "hello"));
	ASSERT(StringUtils::equalsIgnoreCase("HELLO", "hello"));

	return (0);
}

CASE("string-util", "replace")
{
	ASSERT(StringUtils::replace("Hetto", 't', 'l') == "Hello");

	return (0);
}

CASE("string-util", "first")
{
	ASSERT(StringUtils::first("Hello") == 'H');
	ASSERT(StringUtils::first("World") == 'W');
	ASSERT(StringUtils::first("x") == 'x');
	ASSERT(StringUtils::first("") == '\0');

	return (0);
}

CASE("string-util", "last")
{
	ASSERT(StringUtils::last("Hello") == 'o');
	ASSERT(StringUtils::last("World") == 'd');
	ASSERT(StringUtils::last("x") == 'x');
	ASSERT(StringUtils::last("") == '\0');

	return (0);
}
