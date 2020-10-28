/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mime.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:37:47 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/26 17:37:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/mime/Mime.hpp>

Mime::Mime() :
		m_type(),
		m_extensions()
{
}

Mime::Mime(const string &type, const string &extension) :
		m_type(type),
		m_extensions()
{
	m_extensions.push_back(extension);
}

Mime::Mime(const string &type, const list &extensions) :
		m_type(type),
		m_extensions(extensions)
{
}

Mime::Mime(const Mime &other) :
		m_type(other.m_type),
		m_extensions(other.m_extensions)
{
}

Mime&
Mime::operator =(const Mime &other)
{
	if (this != &other)
	{
		m_type = other.m_type;
		m_extensions = other.m_extensions;
	}

	return (*this);
}

const Mime::string&
Mime::type() const
{
	return (m_type);
}

const Mime::list&
Mime::extensions() const
{
	return (m_extensions);
}
