/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Common.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <stddef.h>

#include "Common.hpp"

ssize_t
Common::strict_strstr(const std::string haystack, const std::string needle, size_t start)
{
	size_t index = start;
	size_t jndex = 0;

	if (start >= haystack.size())
		return (-1);
	while (1)
	{
		if (jndex >= needle.size())
			return (index - jndex);
		if (index >= haystack.size())
			return (-1);
		if (haystack.at(index) == needle.at(jndex))
			jndex++;
		else
		{
			index -= jndex;
			jndex = 0;
		}
		index++;
	}
}

std::string
Common::get_file_name(std::string const &file)
{
	size_t index = 0;
	size_t last = 0;

	while (1)
	{
		if (index >= file.length())
			break ;
		if (file.at(index) == '.')
			last = index;
		index++;
	}
	if (last == 0)
		return (file);
	return (file.substr(0, last));
}
