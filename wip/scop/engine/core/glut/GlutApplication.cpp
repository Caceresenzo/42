/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlutApplication.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:40:34 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/08 00:40:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/core/glut/GlutApplication.hpp>
#include <engine/core/glut/GlutWindow.hpp>
#include <engine/exception/IllegalStateException.hpp>
#include <engine/opengl.hpp>
#include <engine/utility/System.hpp>
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <iostream>
#include <vector>

GlutApplication::GlutApplication(const std::string &name) :
		Application(name),
		m_main_window(NULL)
{
	int size = System::arguments.size();
	glutInit(&size, System::arguments.data());

	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
}

GlutApplication::~GlutApplication()
{
}

Window*
GlutApplication::create_window(int width, int height, const std::string &name)
{
	GlutWindow *window = new GlutWindow(width, height);
	window->set_title(name);

	if (!m_main_window)
		m_main_window = window;

	return (window);
}

Window&
GlutApplication::main_window()
{
	if (!m_main_window)
		throw IllegalStateException("no main window yet");

	return (*m_main_window);
}
