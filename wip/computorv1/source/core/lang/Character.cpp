/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 23:04:22 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/29 23:04:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/lang/Character.hpp>
#include <cctype>
#include <locale>

bool
Character::is_digit(char chr)
{
	return (std::isdigit(chr));
}

char
Character::to_uppercase(char chr)
{
	return (std::toupper(chr));
}

bool
Character::is_whitespace(char chr)
{
	return (std::isspace(chr));
}
