/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:40:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:40:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cerrno>
#include <cstring>

#include "CommandFactory.hpp"
#include "Context.hpp"
#include "ICommand.hpp"

#define TABLE_SEPARATOR  "+ ---- + ----------------------------------------------- + ---------------- +"
#define TABLE_HEAD       "| ADDR | CONTENT                                         | PRINTABLE        |"
#define TABLE_DUPLICATE  "| **** | ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** | **************** |"

bool
g_help = false;

bool
g_profiler = false;

bool
g_file = false;

bool
g_stdin = false;

bool
g_dump = false;

bool
g_colored = false;

void
at(std::string source, size_t position)
{
	std::cerr << "at: " << source << std::endl;

	std::cerr << "    ";
	for (size_t index = 0; index < position; ++index)
		std::cerr << " ";

	std::cerr << "^" << std::endl;
	std::cerr << "(position: " << position << ")" << std::endl;
}

int
mindopen(std::string source)
{
	Context context;

	CommandFactory commandFactory;
	for (size_t index = 0; index < source.length(); ++index)
	{
		char c = source.at(index);

		if (std::isspace(c))
			continue;

		ICommand *command = commandFactory.create(c, index);

		if (!command)
		{
			std::cerr << "Failed to create command." << std::endl;
			at(source, index);
			return (EXIT_FAILURE);
		}

		context.addCommand(command);
	}

	unsigned long long executed = 0;

	if (g_profiler)
		std::cerr << "----- PROGRAM -----" << std::endl;

	const clock_t begin_time = clock();

	try
	{
		ICommand *next;
		while ((next = context.next()) && ++executed)
			next->execute(context);
	}
	catch (ICommand::CommandException &e)
	{
		std::cerr << "An error has been detected while running the mindopen interpreter: " << std::endl;
		std::cerr << e.what() << std::endl;

		const ICommand *command = e.command();
		if (command)
			at(source, command->position());
	}

	if (g_profiler)
	{
		std::cerr << std::endl << "----- PROFILER -----" << std::endl;
		std::cerr << "Compiled instruction: " << context.commandCount() << "  " << std::endl;
		std::cerr << "Executed instruction: " << executed << "  " << std::endl;

		float took = float(clock() - begin_time) / CLOCKS_PER_SEC;

		std::cerr << "Execution time: " << std::fixed << std::setprecision(5) << took << "s" << "  " << std::endl;
	}

	if (g_dump)
	{
		std::cerr << std::endl << "----- DUMP -----" << std::endl;
		std::cerr << "Memory size: " << MEMORY_SIZE << "  " << std::endl;

		std::cerr << TABLE_SEPARATOR << std::endl;
		std::cerr << TABLE_HEAD << std::endl;
		std::cerr << TABLE_SEPARATOR << std::endl;

		bool wasSame = false;

		for (int y = 0; y < MEMORY_SIZE / 16; ++y)
		{
			bool same;

			if ((same = y != 0))
			{
				for (int x = 0; x < 16; ++x)
				{
					long addr = y * 16 + x;
					long addrMinusOne = (y - 1) * 16 + x;

					same &= context.memory(addr) == context.memory(addrMinusOne);
				}

				if (!same)
					wasSame = false;
			}

			if (same)
			{
				if (!wasSame)
				{
					std::cerr << TABLE_DUPLICATE << std::endl;
					wasSame = true;
				}
			}
			else
			{
				std::cout << "| " << std::hex << std::setw(4) << (y * 16) << " | ";

				for (int x = 0; x < 16; ++x)
				{
					long addr = y * 16 + x;
					unsigned char c = context.memory(addr);
					int i = c;


					if (g_colored)
					{
						std::stringstream stream;
						stream << (i + 1);

						std::cout << "\e[38;5;" << stream.str() << "m";
					}

					if (c < 16)
						std::cout << "0";

					std::ios::fmtflags savedFlags(std::cout.flags());

					std::cout << std::hex << i << " ";

					std::cout.flags(savedFlags);

					if (g_colored)
						std::cout << "\e[0m";
				}

				std::cout << "| ";

				for (int x = 0; x < 16; ++x)
				{
					long addr = y * 16 + x;
					char c = context.memory(addr);

					std::cout << (std::isprint(c) ? c : '.');
				}

				std::cout << " | " << std::endl;
			}
		}

		std::cerr << TABLE_SEPARATOR << std::endl;
	}

	return (EXIT_SUCCESS);
}

std::string
readStream(std::istream &stream, bool onlyOneLine)
{
	std::string source;

	if (onlyOneLine)
		std::getline(std::cin, source);
	else
	{
		std::stringstream buffer;

		buffer << stream.rdbuf();

		source = buffer.str();
	}

	for (size_t index = 0; index < source.length(); ++index)
		if (std::isspace(source.at(index)))
			source.erase(index--, 1);

	return (source);
}

int
main(int argc, char **argv)
{
	std::string program = argv[0];

	std::string file;
	std::string source;
	std::ifstream fileStream;

	for (int index = 1; index < argc; ++index)
	{
		std::string str = std::string(argv[index]);

		if (str == "-h" || str == "--help")
			g_help = true;
		else if (str == "-p" || str == "--profile")
			g_profiler = true;
		else if (str == "-d" || str == "--dump")
			g_dump = true;
		else if (str == "-c" || str == "--color")
			g_colored = true;
		else if (file.empty() && !g_file && (g_file = true))
			g_stdin = (file = str) == "-";
		else
		{
			std::cerr << "usage: " << program << " <file>" << std::endl;
			return (EXIT_FAILURE);
		}
	}

	if (g_help)
	{
		std::cout << "mindopen, version 1.0" << std::endl << std::endl;
		std::cout << "usage: mindopen [-hp] [file]" << std::endl << std::endl;
		std::cout << " -h --help     : display this help message" << std::endl;
		std::cout << " -p --profiler : enable the profiler" << std::endl;
		std::cout << " -d --dump     : dump the memory" << std::endl;
		std::cout << " -c --color    : add color to the dump" << std::endl;

		return (EXIT_FAILURE);
	}

	if (g_stdin || !g_file)
		return (mindopen(readStream(std::cin, true)));
	else
	{
		fileStream.open(file.c_str(), std::ios::binary | std::ios::in);
		fileStream.peek();

		if (!fileStream.good())
		{
			std::cerr << program << ": " << file << ": " << std::strerror(errno) << std::endl;
			return (EXIT_FAILURE);
		}

		source = readStream(fileStream, false);
		fileStream.close();

		return (mindopen(source));
	}
}
