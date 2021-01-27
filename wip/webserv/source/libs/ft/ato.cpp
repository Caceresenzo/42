/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:28:52 by atetu             #+#    #+#             */
/*   Updated: 2021/01/08 14:43:48 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libs/ft.hpp>

namespace ft
{
	int
	atoi(const char *str)
	{
		int nb = 0;
		int negative = 1;

		while (*str && (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f' || *str == '\r' || *str == ' '))
			str++;

		if (*str == '+' || *str == '-')
		{
			if (*str == '-')
				negative = -1;
			str++;
		}

		char c;
		while (isdigit(c = *str))
		{
			nb = nb * 10 + (c - '0');
			str++;
		}

		return (nb * negative);
	}
}
