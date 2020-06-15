/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Common.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:52:55 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/04 11:52:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Common.hpp"

bool
Common::is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'
	        || c == '\v');
}

bool
Common::is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool
Common::strict_positive_atoi(const char *str, int *out, char line_end)
{
	while (*str && Common::is_whitespace(*str) && *str != line_end)
		str++;
	if (!*str || *str == line_end)
		return (false);
	*out = 0;
	while (*str)
	{
		char c = *str;
		if (c == line_end)
			break;
		if (!Common::is_digit(*str))
			return (false);
		*out *= 10;
		*out += c - '0';
		str++;
	}
	return (true);
}
