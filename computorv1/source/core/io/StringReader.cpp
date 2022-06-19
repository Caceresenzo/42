/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringReader.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:12:08 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/04 20:12:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/io/StringReader.hpp>
#include <core/lang/Character.hpp>

const char StringReader::END_OF_CONTENT = '\0';

StringReader::StringReader(const std::string &string) :
		m_string(string),
		m_start(0),
		m_end(string.size()),
		m_index(m_start)
{
}

StringReader::StringReader(const std::string &string, std::string::size_type start, std::string::size_type end) :
		m_string(string),
		m_start(start),
		m_end(end),
		m_index(m_start)
{
}

StringReader::StringReader(const StringReader &other) :
		m_string(other.m_string),
		m_start(other.m_start),
		m_end(other.m_end),
		m_index(other.m_index)
{
}

char
StringReader::read(void)
{
	char chr = at(m_index);

	m_index = increment(1);

	return (chr);
}

char
StringReader::peek(std::string::size_type n) const
{
	return (at(increment(n)));
}

StringReader&
StringReader::skip(std::string::size_type n)
{
	m_index = increment(n);

	return (*this);
}

StringReader&
StringReader::skip_whitespaces(void)
{
	while (true)
	{
		char chr = peek();

		if (chr == StringReader::END_OF_CONTENT)
			break;

		if (!Character::is_whitespace(chr))
			break;

		skip();
	}

	return (*this);
}

bool
StringReader::is_end_of_content(void) const
{
	return (is_end_of_file_at_index(m_index));
}

std::string::size_type
StringReader::get_index(void) const
{
	return (m_index);
}

bool
StringReader::is_end_of_file_at_index(std::string::size_type index) const
{
	return (index >= m_end);
}

std::string::size_type
StringReader::increment(std::string::size_type n) const
{
	return (std::min(m_index + n, m_end));
}

char
StringReader::at(std::string::size_type index) const
{
	if (is_end_of_file_at_index(index))
		return (StringReader::END_OF_CONTENT);

	return (m_string.at(index));
}
