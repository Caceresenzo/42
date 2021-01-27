/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_util_datasize.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 00:54:37 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/26 00:54:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests/test_unit.hpp>
#include <unit/DataSize.hpp>

CASE("datasize", "parse-invalid")
{
	ASSERT_EXCEPT(DataSize::parse(""));
	ASSERT_EXCEPT(DataSize::parse("x"));
	ASSERT_EXCEPT(DataSize::parse("12x"));

	return (0);
}

CASE("datasize", "parse-default-unit")
{
	ASSERT_NO_EXCEPT(ASSERT(DataSize::parse("1").toBytes() == 1));

	return (0);
}

CASE("datasize", "parse-1unit")
{
	ASSERT_NO_EXCEPT(DataSize::parse("1B"));
	ASSERT_NO_EXCEPT(DataSize::parse("1KB"));
	ASSERT_NO_EXCEPT(DataSize::parse("1MB"));
	ASSERT_NO_EXCEPT(DataSize::parse("1GB"));
	ASSERT_NO_EXCEPT(DataSize::parse("1TB"));

	return (0);
}

CASE("datasize", "parse-only-unit")
{
	ASSERT_NO_EXCEPT(DataSize::parse("B"));
	ASSERT_NO_EXCEPT(DataSize::parse("KB"));
	ASSERT_NO_EXCEPT(DataSize::parse("MB"));
	ASSERT_NO_EXCEPT(DataSize::parse("GB"));
	ASSERT_NO_EXCEPT(DataSize::parse("TB"));

	return (0);
}

CASE("datasize", "parse-negative")
{
	ASSERT_NO_EXCEPT(DataSize::parse("-1B"));
	ASSERT_NO_EXCEPT(DataSize::parse("-1KB"));
	ASSERT_NO_EXCEPT(DataSize::parse("-1MB"));
	ASSERT_NO_EXCEPT(DataSize::parse("-1GB"));
	ASSERT_NO_EXCEPT(DataSize::parse("-1TB"));

	return (0);
}

CASE("datasize", "parse-and-test-value")
{
	ASSERT(DataSize::parse("1B") == DataSize::ofBytes(1));
	ASSERT(DataSize::parse("1KB") == DataSize::ofKilobytes(1));
	ASSERT(DataSize::parse("1MB") == DataSize::ofMegabytes(1));
	ASSERT(DataSize::parse("1GB") == DataSize::ofGigabytes(1));
	ASSERT(DataSize::parse("1TB") == DataSize::ofTerabytes(1));

	return (0);
}

CASE("datasize", "convert")
{
	ASSERT(DataSize::ofBytes(1).toBytes() == 1);
	ASSERT(DataSize::ofKilobytes(1).toBytes() == 1024);
	ASSERT(DataSize::ofMegabytes(1).toBytes() == (long long )1024 * 1024);
	ASSERT(DataSize::ofGigabytes(1).toBytes() == (long long )1024 * 1024 * 1024);
	ASSERT(DataSize::ofTerabytes(1).toBytes() == (long long )1024 * 1024 * 1024 * 1024);

	return (0);
}
