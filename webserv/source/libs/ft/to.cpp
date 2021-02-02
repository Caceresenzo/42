/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:22:51 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/05 01:22:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libs/ft.hpp>

namespace ft
{
	char
	tolower(char c)
	{
		if (isupper(c))
			return (c + 0x20);

		return (c);
	}

	char
	toupper(char c)
	{
		if (islower(c))
			return (c - 0x20);

		return (c);
	}
}
