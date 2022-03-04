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

bool Keyboard::s_states[UCHAR_MAX] = { false };

Keyboard::Keyboard()
{
}

bool
Keyboard::is_pressed(Key key)
{
	return (s_states[key]);
}

void
Keyboard::set_pressed(Key key, bool state)
{
	s_states[key] = state;
}
