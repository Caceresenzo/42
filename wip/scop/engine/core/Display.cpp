/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 01:24:22 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/03 01:24:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/core/Display.hpp>
#include <engine/opengl.hpp>

Display::Display()
{
}

int
Display::x()
{
	return (glutGet(GLUT_WINDOW_X));
}

int
Display::y()
{
	return (glutGet(GLUT_WINDOW_Y));
}

int
Display::width()
{
	return (glutGet(GLUT_WINDOW_WIDTH));
}

int
Display::height()
{
	return (glutGet(GLUT_WINDOW_HEIGHT));
}

Vector<2, int>
Display::size()
{
	return (Vector<2, int>(width(), height()));
}
