/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:17:46 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/08 00:17:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/core/Window.hpp>

Window::~Window()
{
}

void
Window::toggle_fullscreen()
{
	set_fullscreen(!is_fullscreen());
}
