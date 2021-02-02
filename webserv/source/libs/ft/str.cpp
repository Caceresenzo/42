/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:26:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/20 17:26:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libs/ft.hpp>
#include <stddef.h>

namespace ft
{
	size_t
	strlen(const char *str)
	{
		const char *start = str;

		if (str)
			while (*str)
				str++;

		return (str - start);
	}

	char*
	strdup(const char *str)
	{
		if (str)
		{
			size_t len = strlen(str);
			char *dup = new char[len + 1];
			return ((char*)memcpy(dup, str, len + 1));
		}

		return (NULL);
	}

	char*
	strchr(char *str, char c)
	{
		if (str)
		{
			char x;
			while ((x = *str++))
				if (x == c)
					return (--str);
		}

		return (NULL);
	}

}
