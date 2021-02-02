/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:18:05 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 21:18:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json/JsonUtils.hpp>
#include <sstream>

std::string
JsonUtils::escapeString(const std::string &str)
{
	std::string jstr("\"");
	jstr.reserve(str.size() + 2); /* Best case scenario: no escape */

	const char *cstr = str.c_str(); /* Faster than str[i] */
	std::string::size_type len = str.length();

	for (std::string::size_type index = 0; index < len; index++)
	{
		char c = cstr[index];

		if (c >= ' ' && c != 127 && c != '"' && c != '\\')
			jstr += c;
		else
		{
			jstr.reserve(2);
			jstr += '\\';

			switch (c)
			{
				case '"':
				case '\\':
					jstr += c;
					break;

				case '\b':
					jstr += 'b';
					break;

				case '\f':
					jstr += 'f';
					break;

				case '\n':
					jstr += 'n';
					break;

				case '\r':
					jstr += 'r';
					break;

				case '\t':
					jstr += 't';
					break;

				default:
					jstr += 'u';
					jstr += escapeHex(c);
					break;
			}
		}
	}

	jstr += '"';

	return (jstr);
}

std::string
JsonUtils::escapeHex(char c)
{
	std::stringstream sstream;
	sstream << std::hex << (int)c;

	std::string hex = std::string("000") + sstream.str();

	return (hex.substr(hex.length() - 4));
}
