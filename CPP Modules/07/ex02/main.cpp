/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 11:57:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/14 11:57:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>

#define xassert(exp) \
	{ \
		if ((exp)) \
			std::cout << "\e[92mPASSED\e[39m: " << #exp << std::endl; \
		else { \
			std::cout << "\e[91mFAILED\e[39m: " << #exp << "    (line: " << __LINE__ << ")" << std::endl; \
			exit(1); \
		} \
	}

#include "Array.hpp"

int
main(void)
{
	std::string words[] = {
		"Hello", "World", "From", "the", "array", "template", "with", "string", "as", "his", "type"
	};

	Array<std::string> empty;
	xassert(empty.size() == 0);

	try {
		empty[1] = "Hello";

		xassert(!"Should have thrown a IndexOutOfBoundsException");
	} catch (Array<std::string>::IndexOutOfBoundsException &e) {
		xassert(std::string(e.what()) == std::string("index: 1, size: 0"));
	}

	Array<std::string> strings(10);
	xassert(strings.size() == 10);

	unsigned int index;
	for (index = 0; index < 10; ++index) {
		strings[index] = words[index];

		xassert(strings[index] == words[index]);
	}

	try {
		strings[index] = words[index];

		xassert(!"Should have thrown a IndexOutOfBoundsException");
	} catch (Array<std::string>::IndexOutOfBoundsException &e) {
		xassert(std::string(e.what()) == std::string("index: 10, size: 10"));
	}

	try {
		strings[50000] = "";

		xassert(!"Should have thrown a IndexOutOfBoundsException");
	} catch (Array<std::string>::IndexOutOfBoundsException &e) {
		xassert(std::string(e.what()) == std::string("index: 50000, size: 10"));
	}

	try {
		strings[-1] = "";

		xassert(!"Should have thrown a IndexOutOfBoundsException");
	} catch (Array<std::string>::IndexOutOfBoundsException &e) {
		xassert(std::string(e.what()) == std::string("index: -1, size: 10"));
	}

	for (unsigned int index = 0; index < strings.size(); ++index)
	{
		std::cout << "[" << index << "] = " << strings[index] << std::endl;
	}

	Array<int> ints(20);
	xassert(ints.size() == 20);

	for (index = 0; index < 20; ++index) {
		ints[index] = index;

		xassert(ints[index] == index);
	}

	try {
		ints[index] = index;

		xassert(!"Should have thrown a IndexOutOfBoundsException");
	} catch (Array<int>::IndexOutOfBoundsException &e) {
		xassert(std::string(e.what()) == std::string("index: 20, size: 20"));
	}

	for (unsigned int index = 0; index < ints.size(); ++index)
	{
		std::cout << "[" << index << "] = " << ints[index] << std::endl;
	}

	Array<std::string> copy;
	xassert((copy = strings).size() == strings.size());

	xassert(copy[0] == strings[0]);
	xassert(!(copy[0] = "modified").empty() && copy[0] != strings[0]);

	Array<std::string> copyByConstructor(strings);
	xassert(copyByConstructor.size() == strings.size());
}
