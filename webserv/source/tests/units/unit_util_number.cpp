/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_util_number.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 23:18:21 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/30 23:18:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests/test_unit.hpp>
#include <util/Number.hpp>

CASE("number", "parse-invalid")
{
	ASSERT_EXCEPT(Number::parse<int>("a", Number::DECIMAL));

	return (0);
}

CASE("number", "out-of-range")
{
	ASSERT_EXCEPT(Number::parse<char>("5000", Number::DECIMAL));
	ASSERT_EXCEPT(Number::parse<char>("-5000", Number::DECIMAL));

	ASSERT_EXCEPT(Number::parse<short>("5000000", Number::DECIMAL));
	ASSERT_EXCEPT(Number::parse<short>("-5000000", Number::DECIMAL));

	return (0);
}

CASE("number", "parse-bin")
{
	ASSERT(Number::parse<int>("1", Number::BIN) == 1);
	ASSERT(Number::parse<int>("-1", Number::BIN) == -1);

	ASSERT(Number::parse<int>("10", Number::BIN) == 2);
	ASSERT(Number::parse<int>("-10", Number::BIN) == -2);

	ASSERT(Number::parse<int>("100", Number::BIN) == 4);
	ASSERT(Number::parse<int>("-100", Number::BIN) == -4);

	return (0);
}

CASE("number", "parse-decimal")
{
	ASSERT(Number::parse<int>("1", Number::DECIMAL) == 1);
	ASSERT(Number::parse<int>("-1", Number::DECIMAL) == -1);
	ASSERT(Number::parse<int>("10", Number::DECIMAL) == 10);
	ASSERT(Number::parse<int>("-10", Number::DECIMAL) == -10);
	ASSERT(Number::parse<int>("100", Number::DECIMAL) == 100);
	ASSERT(Number::parse<int>("-100", Number::DECIMAL) == -100);

	return (0);
}

CASE("number", "parse-hex")
{
	ASSERT(Number::parse<int>("1", Number::HEX) == 1);
	ASSERT(Number::parse<int>("-1", Number::HEX) == -1);
	ASSERT(Number::parse<int>("10", Number::HEX) == 16);
	ASSERT(Number::parse<int>("-10", Number::HEX) == -16);
	ASSERT(Number::parse<int>("100", Number::HEX) == 256);
	ASSERT(Number::parse<int>("-100", Number::HEX) == -256);

	return (0);
}
