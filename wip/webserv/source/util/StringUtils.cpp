/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 20:48:42 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/08 14:44:27 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libs/ft.hpp>
#include <util/CharacterUtils.hpp>
#include <util/StringUtils.hpp>
#include <algorithm>
#include <cctype>

std::string
StringUtils::toUpperCase(const std::string &string) // TODO Find something faster, every solution on the internet are not allowed to us
{
	std::string out;
	out.reserve(string.size() + 1);

	const char *cstr = string.c_str();
	std::string::size_type size = string.size();

	for (std::string::size_type index = 0; index < size; index++)
		out += ft::toupper(cstr[index]);

	return (out);
}

std::string
StringUtils::replace(const std::string &in, char c, char to)
{
	std::string out(in);

	std::replace(out.begin(), out.end(), c, to);

	return (out);
}

bool
StringUtils::equalsIgnoreCase(const std::string &a, const std::string &b)
{
	std::string::size_type size = a.size();
	if (b.size() != size)
		return (false);

	for (std::string::size_type index = 0; index < size; ++index)
		if (tolower(a[index]) != tolower(b[index]))
			return (false);

	return (true);
}

char
StringUtils::first(const std::string &string)
{
	return (string.c_str()[0]);
}

char
StringUtils::last(const std::string &string)
{
	std::string::size_type len = string.length();

	return (string.c_str()[len ? len - 1 : 0]);
}

bool
StringUtils::InsensitiveCompare::operator ()(const std::string &s1, const std::string &s2) const
{
	return (std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), CharacterUtils::InsensitiveCompare()));
}

bool
StringUtils::all(const std::string &string, bool
(*predicate)(char))
{
	if (!predicate)
		return (true);

	for (std::string::size_type index = 0; index < string.size(); index++)
		if (!(*(predicate))(string[index]))
			return (false);

	return (true);
}
