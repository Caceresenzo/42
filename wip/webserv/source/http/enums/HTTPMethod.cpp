/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPMethod.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:32:53 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/18 14:51:52 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/enums/HTTPMethod.hpp>
#include <http/handler/methods/ConnectHandler.hpp>
#include <http/handler/methods/DeleteHandler.hpp>
#include <http/handler/methods/GetHandler.hpp>
#include <http/handler/methods/OptionsHandler.hpp>
#include <http/handler/methods/PutHandler.hpp>
#include <http/handler/methods/TraceHandler.hpp>
#include <http/handler/methods/PostHandler.hpp>

#define DEFINE_METHOD(name, hasBody, handler) ENUM_DEFINE(HTTPMethod, name, HTTPMethod(hasBody, &handler));

DEFINE_METHOD(GET,/*     */false, GetHandler::instance());
DEFINE_METHOD(HEAD,/*    */false, GetHandler::instance());
DEFINE_METHOD(POST,/*     */true, PostHandler::instance());
DEFINE_METHOD(PUT,/*      */true, PutHandler::instance());
DEFINE_METHOD(DELETE,/*  */false, DeleteHandler::instance());
DEFINE_METHOD(CONNECT,/* */false, ConnectHandler::instance());
DEFINE_METHOD(OPTIONS,/* */false, OptionsHandler::instance());
DEFINE_METHOD(TRACE,/*   */false, TraceHandler::instance());

HTTPMethod::HTTPMethod(void) :
		m_hasBody(),
		m_handler()
{
}

HTTPMethod::HTTPMethod(bool hasBody, HTTPMethodHandler *handler) :
		m_hasBody(hasBody),
		m_handler(handler)
{
}

HTTPMethod::HTTPMethod(const HTTPMethod &other) :
		m_hasBody(other.m_hasBody),
		m_handler(other.m_handler)
{
}

HTTPMethod::~HTTPMethod(void)
{
}

HTTPMethod&
HTTPMethod::operator =(const HTTPMethod &other)
{
	Enum::operator=(other);

	if (this != &other)
	{
		m_hasBody = other.m_hasBody;
		m_handler = other.m_handler;
	}

	return (*this);
}

bool
HTTPMethod::hasBody(void) const
{
	return (m_hasBody);
}

HTTPMethodHandler&
HTTPMethod::handler(void) const
{
	return (*m_handler);
}
