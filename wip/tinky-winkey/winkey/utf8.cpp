/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utf8.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:57:38 by ecaceres          #+#    #+#             */
/*   Updated: 2023/01/09 00:57:38 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "winkey.hpp"

BOOL IsAllPrintable(CHAR *buffer, UINT length)
{
	for (UINT index = 0; index != length; ++index)
	{
		CHAR low = buffer[index] & 0x7f;
		if (!isprint(low))
			return (false);
	}

	return (true);
}

/* thanks https://github.com/cflaviu/to_uft8/blob/main/inc/to_utf8/from_utf32.hpp */
BOOL ConvertToUTF8(CHAR *buffer, const int codePoint)
{
	if (codePoint < 0x7F)
	{
		buffer[0] = static_cast<char>(codePoint & 0xFF);
		buffer[1] = '\0';
		return (true);
	}

	if (codePoint < 0x7FF)
	{
		buffer[0] = static_cast<char>(192u | ((codePoint >> 6u) & 0b111111));
		buffer[1] = static_cast<char>(128u | ((codePoint % 64u) & 0b111111));
		buffer[2] = '\0';
		return (true);
	}

	if (codePoint < 0xFFFF)
	{
		buffer[0] = static_cast<char>(224u | ((codePoint >> 12u) & 0b1111));
		buffer[1] = static_cast<char>(128u | ((codePoint >> 6u) & 0b111111));
		buffer[2] = static_cast<char>(128u | ((codePoint % 64u) & 0b111111));
		buffer[3] = '\0';
		return (true);
	}

	if (codePoint < 0x1FFFFF)
	{
		buffer[0] = static_cast<char>(240u | ((codePoint >> 18u) & 0b1111));
		buffer[1] = static_cast<char>(128u | ((codePoint >> 12u) & 0b111111));
		buffer[2] = static_cast<char>(128u | ((codePoint >> 6u) & 0b111111));
		buffer[3] = static_cast<char>(128u | ((codePoint % 64u) & 0b111111));
		buffer[4] = '\0';
		return (true);
	}

	std::cerr << "ConvertToUTF8" << std::endl;
	// unsupported for 4 bytes?
	return (false);
}
