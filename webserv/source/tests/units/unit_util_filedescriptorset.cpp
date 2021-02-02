/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_util_filedescriptorset.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 02:14:38 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/08 02:14:38 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests/test_unit.hpp>
#include <util/FileDescriptorSet.hpp>

CASE("filedescriptorset", "zero")
{
	FileDescriptorSet fdSet;

	fdSet.set(42);
	fdSet.set(24);

	fdSet.zero();
	ASSERT(!fdSet.test(42));
	ASSERT(!fdSet.test(24));
	ASSERT(fdSet.empty());

	return (0);
}

CASE("filedescriptorset", "set")
{
	FileDescriptorSet fdSet;

	fdSet.set(42);
	ASSERT(fdSet.test(42));

	fdSet.set(24);
	ASSERT(fdSet.test(24));

	return (0);
}

CASE("filedescriptorset", "clear")
{
	FileDescriptorSet fdSet;

	fdSet.set(42);
	fdSet.set(24);

	fdSet.clear(42);
	ASSERT(!fdSet.test(42));

	fdSet.clear(24);
	ASSERT(!fdSet.test(24));

	return (0);
}

CASE("filedescriptorset", "size")
{
	FileDescriptorSet fdSet;

	ASSERT(fdSet.size() == 0);

	fdSet.set(42);
	ASSERT(fdSet.size() == 1);

	fdSet.set(24);
	ASSERT(fdSet.size() == 2);

	fdSet.clear(24);
	ASSERT(fdSet.size() == 1);

	fdSet.clear(42);
	ASSERT(fdSet.size() == 0);

	return (0);
}

CASE("filedescriptorset", "empty")
{
	FileDescriptorSet fdSet;

	ASSERT(fdSet.empty());

	fdSet.set(42);
	ASSERT(!fdSet.empty());

	return (0);
}
