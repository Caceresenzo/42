/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Application.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:18:58 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/08 00:18:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/application/Application.hpp>
#include <lang/IllegalStateException.hpp>
#include <engine/opengl.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>

static void
error_callback(int, const char *description)
{
	fprintf(stderr, "Error: %s\n", description);
}

Application *Application::m_instance = NULL;

Application::Application(const std::string &name) :
		m_name(name)
{
	if (m_instance)
		throw IllegalStateException("already created");

	m_instance = this;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		throw RuntimeException("could not initialize backend");
}

Application::~Application()
{
	m_instance = NULL;

	glfwTerminate();
}

void
Application::poll_events()
{
	glfwPollEvents();
}

Application&
Application::instance()
{
	if (!m_instance)
		throw IllegalStateException("not yet available");

	return (*m_instance);
}
