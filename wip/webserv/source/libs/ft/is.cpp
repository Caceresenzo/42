/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 01:22:51 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/08 14:43:43 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libs/ft.hpp>

namespace ft
{
	bool
	islower(char c)
	{
		return (c >= 'a' && c <= 'z');
	}

	bool
	isupper(char c)
	{
		return (c >= 'A' && c <= 'Z');
	}

	bool
	isdigit(char c)
	{
		return (c >= '0' && c <= '9');
	}
}
