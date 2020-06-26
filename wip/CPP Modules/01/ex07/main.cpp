/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <cerrno>
#include <cstring>

#include "TheReplacer.hpp"

#define CHECK_EMPTY(str) \
	{ \
		if (str.empty()) \
		{ \
			valid = false; \
			std::cerr << program << ": argument " << #str << " should not be empty." << std::endl; \
		} \
	}

int
main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "usage: replace <file> <s1> <s2>" << std::endl;
		return (1);
	}

	std::string program(argv[0]);
	std::string file(argv[1]);
	std::string s1(argv[2]);
	std::string s2(argv[3]);

	bool valid = true;
	CHECK_EMPTY(file);
	CHECK_EMPTY(s1);
	CHECK_EMPTY(s2);

	if (!valid)
	{
		std::cerr << program << ": error found, aborting." << std::endl;
		return (1);
	}

	TheReplacer replacer(file, s1, s2);

	int error = replacer.replace();
	if (error)
	{
		std::cerr << program << ": " << file << ": " << std::strerror(errno) << std::endl;
		return (1);
	}

	return (0);
}
