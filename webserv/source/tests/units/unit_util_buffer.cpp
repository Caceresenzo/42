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
#include <buffer/impl/BaseBuffer.hpp>
#include <string>

CASE("buffer", "base-store")
{
	ASSERT(BaseBuffer().store('x').storage() == "x");
	ASSERT(BaseBuffer().store(std::string("hello")).storage() == "hello");
	ASSERT(BaseBuffer().store("hello", 5).storage() == "hello");

	return (0);
}

CASE("buffer", "store-other")
{
	BaseBuffer helloWorld;
	helloWorld.store("Hello World");

	ASSERT(BaseBuffer(8).store(helloWorld).size() == 8);
	ASSERT(helloWorld.size() == 3);

	helloWorld.clear();
	helloWorld.store("Hello World");

	ASSERT(BaseBuffer(8).store(helloWorld, false).size() == 8);
	ASSERT(helloWorld.size() == 11);

	return (0);
}

CASE("buffer", "capacity")
{
	ASSERT(BaseBuffer(8).store('x').capacity() == 7);
	ASSERT(BaseBuffer(8).store("Hello World").capacity() == 0);

	return (0);
}
