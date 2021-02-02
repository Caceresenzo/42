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

#include <net/address/Inet4Address.hpp>
#include <net/address/Inet6Address.hpp>
#include <net/address/InetSocketAddress.hpp>
#include <tests/test_unit.hpp>
#include <string>

CASE("net-address", "4")
{
	ASSERT(Inet4Address().hostAddress() == "0.0.0.0");
	ASSERT(Inet4Address(127, 0, 0, 1).hostAddress() == "127.0.0.1");
	ASSERT(Inet4Address(255, 255, 255, 255).hostAddress() == "255.255.255.255");

	ASSERT(Inet4Address::parse(0).hostAddress() == "0.0.0.0");

	return (0);
}

CASE("net-address", "4-validation")
{
	ASSERT(Inet4Address::validate("0.0.0.0"));
	ASSERT(Inet4Address::validate("1.1.1.1"));
	ASSERT(Inet4Address::validate("255.255.255.255"));
	ASSERT(!Inet4Address::validate("a"));
	ASSERT(!Inet4Address::validate("1.1.1.a"));
	ASSERT(!Inet4Address::validate("1.1.1.1a"));
	ASSERT(!Inet4Address::validate("1.1.1.1.1"));
	ASSERT(!Inet4Address::validate("1.1.1"));
	ASSERT(!Inet4Address::validate(""));
	ASSERT(!Inet4Address::validate("a.a.a.a"));
	ASSERT(!Inet4Address::validate("300.300.300.300"));
	ASSERT(!Inet4Address::validate("11111.11111.11111.11111"));
	ASSERT(!Inet4Address::validate("0.11111.0.0"));
	ASSERT(!Inet4Address::validate("0 .0.0 .0"));

	return (0);
}

CASE("net-address", "6")
{
	ASSERT(Inet6Address().hostAddress() == "0:0:0:0:0:0:0:0");
	ASSERT(Inet6Address(0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x7f00, 0x0001).hostAddress() == "0:0:0:0:0:ffff:7f00:1");
	ASSERT(Inet6Address(0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff).hostAddress() == "0:0:0:0:0:ffff:ffff:ffff");

	return (0);
}

CASE("net-address", "sock")
{
	ASSERT(InetSocketAddress().hostAddress() == ":0");
	ASSERT(InetSocketAddress(80).hostAddress() == ":80");

	return (0);
}

CASE("net-address", "sock4")
{
	Inet4Address template127(127, 0, 0, 1);
	Inet4Address template255(255, 255, 255, 255);

	ASSERT(InetSocketAddress(template127, 80).hostAddress() == "127.0.0.1:80");
	ASSERT(InetSocketAddress(template255, 80).hostAddress() == "255.255.255.255:80");
	ASSERT(InetSocketAddress(template127, 12345).hostAddress() == "127.0.0.1:12345");
	ASSERT(InetSocketAddress(template255, 12345).hostAddress() == "255.255.255.255:12345");

	return (0);
}

CASE("net-address", "sock6")
{
	Inet6Address template127(0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x7f00, 0x0001);
	Inet6Address template255(0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff);

	ASSERT(InetSocketAddress(template127, 80).hostAddress() == "[0:0:0:0:0:ffff:7f00:1]:80");
	ASSERT(InetSocketAddress(template255, 80).hostAddress() == "[0:0:0:0:0:ffff:ffff:ffff]:80");
	ASSERT(InetSocketAddress(template127, 12345).hostAddress() == "[0:0:0:0:0:ffff:7f00:1]:12345");
	ASSERT(InetSocketAddress(template255, 12345).hostAddress() == "[0:0:0:0:0:ffff:ffff:ffff]:12345");

	return (0);
}
