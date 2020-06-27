/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TheReplacer.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TheReplacer.hpp"

#include <stddef.h>
#include <iostream>
#include <string>

#include <cerrno>
#include <cstring>

TheReplacer::TheReplacer(std::string &file, std::string &s1, std::string &s2) : _file(file), _s1(s1), _s2(s2)
{
	this->_outFile = file + ".replace";
}

int
TheReplacer::_readInputFile(std::string &dest)
{
	this->_in.open(this->_file.c_str());

	if (errno)
		return (errno);

	if (this->_in.is_open())
	{
		std::string line;
		while (std::getline(this->_in, line))
		{
			dest.append(line);

			if (!this->_in.eof())
				dest.append("\n");
		}
	}

	return (0);
}

int
TheReplacer::_writeOutputFile(std::string &src)
{
	this->_out.open(this->_outFile.c_str());

	if (!errno)
	{
		if (this->_out.is_open())
			this->_out << src;
	}
	return (errno);
}

void
TheReplacer::_closeStreams(void)
{
	if (this->_in.is_open())
		this->_in.close();

	if (this->_out.is_open())
		this->_out.close();
}

int
TheReplacer::replace(void)
{
	int error;

	std::string input;
	if ((error = _readInputFile(input)))
		return (error);

	size_t start = 0;
	size_t charIndex;

	std::string replaced;

	if (this->_s1 == this->_s2)
		replaced = input;
	else
	{
		while (true)
		{
			charIndex = input.find(this->_s1, start);

			if (charIndex == std::string::npos)
			{
				replaced.append(input, start, input.length());
				break;
			}

			replaced.append(input, start, charIndex - start);
			replaced.append(this->_s2);

			start = charIndex + this->_s1.length();
		}
	}

	if ((error = _writeOutputFile(replaced)))
		return (error);

	if (DEBUG_REPLACER)
	{
		std::cout << "OUT FILE : " << this->_outFile << std::endl;
		std::cout << "s1       : ..." << this->_s1 << "..." << std::endl;
		std::cout << "s2       : ..." << this->_s2 << "..." << std::endl;
		std::cout << "input    : ..." << input << "..." << std::endl;
		std::cout << "output   : ..." << replaced << "..." << std::endl;
	}

	return (0);
}
