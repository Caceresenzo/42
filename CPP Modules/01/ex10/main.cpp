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

#ifndef PROGRAM_NAME
# define PROGRAM_NAME "cato9tails"
#endif

int g_exitCode = 0;

void
displayErrno(std::string &file)
{
	if (errno)
	{
		g_exitCode = 1;
		std::cerr << PROGRAM_NAME << ": " << file << ": " << std::strerror(errno) << std::endl;
	}
}

void
handleStream(std::string file, std::istream &stream)
{
	std::string read;

	stream.peek();
	if (!stream.good())
		displayErrno(file);
	while (stream.good())
	{
		std::getline(stream, read);
		std::cout << read;

		if (stream.eof())
			break;

		std::cout << std::endl;
	}
}

int
main(int argc, char **argv)
{
	if (argc == 1)
		handleStream("", std::cin);
	else
	{
		std::ifstream stream;

		for (int index = 1; index < argc; index++)
		{
			errno = 0;

			std::string file = std::string(argv[index]);

			if (file == "-")
				handleStream(file, std::cin);
			else
			{
				stream.open(file.c_str(), std::ifstream::in);

				if (stream.is_open())
				{
					handleStream(file, stream);
					stream.close();
				}
				else
					displayErrno(file);
			}
		}
	}

	return (g_exitCode);
}
