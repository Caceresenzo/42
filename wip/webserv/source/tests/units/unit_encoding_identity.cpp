/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_encoding_identity.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 00:58:35 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/21 18:33:06 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/body/encoding/identity/IdentityDecoder.hpp>
#include <http/body/encoding/identity/IdentityEncoder.hpp>
#include <libs/ft.hpp>
#include <tests/test_unit.hpp>
#include <util/Singleton.hpp>
#include <string>

static std::string
encode(const char *str)
{
	return (IdentityEncoder::instance().encode(str));
}

static std::string
decode(const char *str)
{
	return (IdentityDecoder(false, ft::strlen(str)).decode(str, false));
}

static std::string
decode2(const char *str, const char *str2)
{
	IdentityDecoder decoder(false, ft::strlen(str) + ft::strlen(str2));

	size_t consumed = 0;
	std::string out;
	decoder.consume(str, out, consumed, false);
	decoder.consume(str2, out, consumed, false);

	return (out);
}

CASE("identity", "encode")
{
	ASSERT(encode("Hello") == "Hello");
	ASSERT(encode("World") == "World");

	return (0);
}

CASE("identity", "decode")
{
	ASSERT(decode("Hello") == "Hello");
	ASSERT(decode("World") == "World");

	return (0);
}

CASE("identity", "decode2")
{
	ASSERT(decode2("Hello ", "World") == "Hello World");
	ASSERT(decode2("HelloWorld", "") == "HelloWorld");

	return (0);
}

