/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyboardListener.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:47:37 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 19:47:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/application/Window.hpp>
#include <engine/control/Keyboard.hpp>
#include <game/listener/KeyboardListener.hpp>

KeyboardListener::KeyboardListener()
{
}

KeyboardListener::~KeyboardListener()
{
}

void
KeyboardListener::on_key_press(Window &window, Keyboard::Key key)
{
	Keyboard::set_pressed(key, true);

	if (key == Keyboard::F)
		window.toggle_fullscreen();
	else if (key == Keyboard::ESCAPE)
		window.set_should_close(true);
}

void
KeyboardListener::on_key_release(Window&, Keyboard::Key key)
{
	Keyboard::set_pressed(key, false);
}
