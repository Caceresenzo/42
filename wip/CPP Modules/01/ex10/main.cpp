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
#include <errno.h>

#ifndef PROGRAM_NAME
# define PROGRAM_NAME "cato9tails"
#endif

int g_exitCode = 0;


/*
** Note:
** It seems that thanks to unix, /dev/stdin is not a file, and so, is not supported by the ifstream...
**
** https://github.com/bigartm/bigartm/pull/258#issuecomment-128131871
**
** Its ugly, very ugly, way too ugly, but "it works"...
** But does not handle other /dev/ files. (e.g. /dev/tty)
*/

bool
isUnixStdFile(std::string file)
{
	return (file == "/dev/stdin" || file == "/dev/stdout" || file == "/dev/stderr"
			|| file == "/dev/fd/0" || file == "/dev/fd/1" || file == "/dev/fd/2");
}

void
displayErrno(std::string file)
{
	if (errno)
	{
		g_exitCode = 1;
		std::cerr << PROGRAM_NAME << ": " << file << ": " << strerror(errno) << std::endl;
	}
}

void
handleStream(std::string file, std::istream &stream)
{
	std::string read;

	while (stream.good())
	{
		std::getline(stream, read);
		std::cout << read;

		if (stream.eof())
		{
			break;
		}

		std::cout << std::endl;
	}

	if (!stream.good())
	{
		displayErrno(file);
	}
}

int
main(int argc, char **argv)
{
	if (argc == 1)
	{
		handleStream("", std::cin);
	}
	else
	{
		for (int index = 1; index < argc; index++)
		{
			errno = 0;

			std::string file = std::string(argv[index]);

			if (isUnixStdFile(file))
			{
				handleStream(file, std::cin);
			}
			else
			{
				std::ifstream stream(file);

				if (stream.is_open())
				{
					handleStream(file, stream);
					stream.close();
				}
				else
				{
					displayErrno(file);
				}
			}
		}
	}

	return (g_exitCode);
}
