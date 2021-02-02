/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringResponseBody.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:10:52 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/27 10:29:58 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/response/body/impl/StringResponseBody.hpp>

StringResponseBody::StringResponseBody() :
		m_content()
{
}

StringResponseBody::StringResponseBody(const std::string &content) :
		m_content(content)
{
}

StringResponseBody::~StringResponseBody()
{
}

StringResponseBody::StringResponseBody(const StringResponseBody &other) :
		m_content(other.m_content)
{
}

StringResponseBody&
StringResponseBody::operator=(const StringResponseBody &other)
{
	if (this != &other)
		m_content = other.m_content;

	return (*this);
}

bool
StringResponseBody::store(BaseBuffer &buffer)
{
	buffer.store(m_content);

	return (true);
}
