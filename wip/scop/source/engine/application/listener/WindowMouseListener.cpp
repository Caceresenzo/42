/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WindowMouseListener.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:39:03 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 19:39:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/application/listener/WindowMouseListener.hpp>
#include <engine/application/Window.hpp>

WindowMouseListener::~WindowMouseListener()
{
}

void
WindowMouseListener::on_mouse_move(Window&, const Vector<2, int>&)
{
}

void
WindowMouseListener::on_mouse_scroll(Window&, const Vector<2, int>&)
{
}
