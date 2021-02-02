/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_http_parser_path.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 22:11:42 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/01 22:11:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/header/HTTPHeaderFields.hpp>
#include <http/parser/HTTPHeaderFieldsParser.hpp>
#include <tests/test_unit.hpp>

static HTTPHeaderFields
parse(const char *str)
{
	HTTPHeaderFieldsParser parser;

	while (*str)
		parser.consume(*str++);

	return (parser.headerFields());
}

CASE("http-parser-headerfields", "normal")
{
	ASSERT(parse("") == HTTPHeaderFields());
	ASSERT(parse("Hello: World\r\n") == HTTPHeaderFields().set("Hello", "World"));
	ASSERT(parse("Hello: World\r\nFrom: Unit-Testing\r\n") == HTTPHeaderFields().set("Hello", "World").set("From", "Unit-Testing"));

	return (0);
}
