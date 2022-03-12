/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlutWindow.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:18:19 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/08 00:18:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/core/glut/GlutWindow.hpp>
#include <engine/opengl.hpp>

GlutWindow::GlutWindow(int width, int height)
{
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	m_window = glutCreateWindow("glut");
	if (m_window < 1)
		throw RuntimeException("could not create window");

	glewExperimental = GL_TRUE;
	GLint glew_init_result = glewInit();
	if (GLEW_OK != glew_init_result)
	{
		std::string error = reinterpret_cast<const char*>(glewGetErrorString(glew_init_result));
		glutDestroyWindow(m_window);

		throw RuntimeException("could not initialize glew: " + error);
	}
}

GlutWindow::~GlutWindow()
{
	glutDestroyWindow(m_window);
}

void
GlutWindow::set_title(const std::string &title)
{
	set_active();

	glutSetWindowTitle(title.c_str());
}

bool
GlutWindow::is_fullscreen() const
{
	set_active();

	return (glutGet(GLUT_FULL_SCREEN) == 1);
}

void
GlutWindow::set_fullscreen(bool fullscreen)
{
	set_active();

	if (fullscreen)
		glutFullScreen();
	else
		glutLeaveFullScreen();
}

void
GlutWindow::toggle_fullscreen()
{
	set_active();
}

Vector<2, int>
GlutWindow::position() const
{
	set_active();

	int x = glutGet(GLUT_WINDOW_X);
	int y = glutGet(GLUT_WINDOW_Y);

	return (Vector<2, int>(x, y));
}

Vector<2, int>
GlutWindow::size() const
{
	set_active();

	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	return (Vector<2, int>(width, height));
}

void
GlutWindow::set_active() const
{
	glutSetWindow(m_window);
}
