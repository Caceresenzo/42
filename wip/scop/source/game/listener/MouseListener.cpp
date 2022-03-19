/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MouseListener.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:48:57 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 19:48:57 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/application/listener/WindowMouseListener.hpp>
#include <engine/application/Window.hpp>
#include <game/listener/MouseListener.hpp>

MouseListener::MouseListener(SharedReference<ICamera> &camera) :
		WindowMouseListener(),
		m_camera(camera)
{
}

MouseListener::~MouseListener()
{
}

void
MouseListener::on_mouse_move(Window &window, const Vector<2, int> &position)
{
	Vector<2, int> center = window.size() / 2;
	Vector<2, int> offset = position - center;

	if (offset != Vector<2, int>::ZERO)
	{
		offset.y = -offset.y;

		m_camera->look(offset);

		window.set_cursor_position(center);
	}
}
