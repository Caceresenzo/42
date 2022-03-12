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

#include <engine/core/Application.hpp>
#include <engine/exception/IllegalStateException.hpp>

Application *Application::m_instance = NULL;

Application::Application(const std::string &name) :
		m_name(name)
{
	if (m_instance)
		throw IllegalStateException("already created");

	m_instance = this;
}

Application::~Application()
{
	m_instance = NULL;
}

Application&
Application::instance()
{
	if (!m_instance)
		throw IllegalStateException("not yet available");

	return (*m_instance);
}
