/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwApplication.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 00:40:47 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/08 00:40:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/core/glfw/GlfwApplication.hpp>
#include <engine/exception/RuntimeException.hpp>
#include <engine/opengl.hpp>
#include <GLFW/glfw3.h>

GlfwApplication::GlfwApplication()
{
	if (!glfwInit())
		throw RuntimeException("could not initialize glfw");
}

GlfwApplication::~GlfwApplication()
{
	glfwTerminate();
}
