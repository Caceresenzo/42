/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwWindow.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:32:24 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/08 00:32:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/core/glfw/GlfwWindow.hpp>
#include <engine/exception/UnsupportedOperationException.hpp>
#include <engine/opengl.hpp>
#include <GLFW/glfw3.h>

bool
GlfwWindow::is_fullscreen() const
{
	throw UnsupportedOperationException();
}

void
GlfwWindow::set_fullscreen(bool)
{
	throw UnsupportedOperationException();
}

void
GlfwWindow::toggle_fullscreen()
{
	throw UnsupportedOperationException();
}

Vector<2, int>
GlfwWindow::size() const
{
	int width = 0;
	int height = 0;

	glfwGetWindowSize(m_window, &width, &height);

	return (Vector<2, int>(width, height));
}
