/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 22:10:43 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 22:10:43 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lang/Character.hpp>

char
Character::to_upper_case(char character)
{
	if (is_lower_case(character))
		return (character - 0x20);

	return (character);
}

bool
Character::is_upper_case(char character)
{
	return (character >= 'A' && character <= 'Z');
}

char
Character::to_lower_case(char character)
{
	if (is_upper_case(character))
		return (character + 0x20);

	return (character);
}

bool
Character::is_lower_case(char character)
{
	return (character >= 'a' && character <= 'z');
}

bool
Character::is_digit(char character)
{
	return (character >= '0' && character <= '9');
}
