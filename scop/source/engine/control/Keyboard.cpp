/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Keyboard.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 23:54:03 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/27 23:54:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/control/Keyboard.hpp>
#include <iostream>

Keyboard::PressState Keyboard::s_states[Keyboard::_LENGTH] = { Keyboard::UNPRESSED };

Keyboard::Keyboard()
{
}

Keyboard::PressState
Keyboard::is_pressed(Key key)
{
	return (s_states[key]);
}

void
Keyboard::set_pressed(Key key, bool state)
{
	s_states[key] = state ? Keyboard::JUST_PRESSED : Keyboard::UNPRESSED;
}

void
Keyboard::increment()
{
	for (unsigned index = 0; index < UCHAR_MAX; ++index)
		if (s_states[index] == Keyboard::JUST_PRESSED)
			s_states[index] = Keyboard::PRESSED;
}
