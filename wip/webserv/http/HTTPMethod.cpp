/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPMethod.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:32:53 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/27 17:32:53 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/HTTPMethod.hpp>

std::vector<HTTPMethod> HTTPMethod::s_DEFAULTS;

HTTPMethod::HTTPMethod(void) :
		m_name()
{
}

HTTPMethod::HTTPMethod(const std::string &name) :
		m_name(name)
{
}

HTTPMethod::HTTPMethod(const HTTPMethod &other) :
		m_name(other.m_name)
{
}

HTTPMethod&
HTTPMethod::operator =(const HTTPMethod &other)
{
	if (this != &other)
		m_name = other.m_name;

	return (*this);
}

const std::string&
HTTPMethod::name(void) const
{
	return (m_name);
}

void
HTTPMethod::loadDefaults(void)
{
	s_DEFAULTS.push_back(HTTPMethod("GET"));
	s_DEFAULTS.push_back(HTTPMethod("HEAD"));
	s_DEFAULTS.push_back(HTTPMethod("POST"));
	s_DEFAULTS.push_back(HTTPMethod("PUT"));
	s_DEFAULTS.push_back(HTTPMethod("DELETE"));
	s_DEFAULTS.push_back(HTTPMethod("CONNECT"));
	s_DEFAULTS.push_back(HTTPMethod("OPTIONS"));
	s_DEFAULTS.push_back(HTTPMethod("TRACE"));
}

const std::vector<HTTPMethod>&
HTTPMethod::defaults(void)
{
	return (s_DEFAULTS);
}

std::ostream&
operator <<(std::ostream &stream, const HTTPMethod &method)
{
	return (stream << method.name());
}
