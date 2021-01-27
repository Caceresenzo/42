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

#include <http/parser/HTTPRequestPathParser.hpp>
#include <tests/test_unit.hpp>
#include <string>

static std::string
parse(const char *str)
{
	HTTPRequestPathParser parser;

	while (*str)
		parser.consume(*str++);

	return (parser.path());
}

CASE("http-parser-path", "normal")
{
	ASSERT(parse("") == "/");
	ASSERT(parse("hello") == "/hello");
	ASSERT(parse("hello/world") == "/hello/world");

	return (0);
}

CASE("http-parser-path", "simple-decode")
{
	ASSERT(parse("hello%20world") == "/hello world");
	ASSERT(parse("hello%2520world") == "/hello%20world");

	return (0);
}
