/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHandlingFilter.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 00:28:17 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/11 16:01:18 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception/Exception.hpp>
#include <http/enums/HTTPMethod.hpp>
#include <http/enums/HTTPStatus.hpp>
#include <http/filter/FilterChain.hpp>
#include <http/filter/impl/between/MethodHandlingFilter.hpp>
#include <http/handler/HTTPMethodHandler.hpp>
#include <http/request/HTTPRequest.hpp>
#include <http/response/HTTPResponse.hpp>
#include <log/Logger.hpp>
#include <log/LoggerFactory.hpp>
#include <util/Optional.hpp>
#include <iostream>
#include <string>

Logger &MethodHandlingFilter::LOG = LoggerFactory::get("Meth. Handl. Filter");

MethodHandlingFilter::MethodHandlingFilter()
{
}

MethodHandlingFilter::MethodHandlingFilter(const MethodHandlingFilter &other)
{
	(void)other;
}

MethodHandlingFilter::~MethodHandlingFilter()
{
}

MethodHandlingFilter&
MethodHandlingFilter::operator=(const MethodHandlingFilter &other)
{
	(void)other;

	return (*this);
}

void
MethodHandlingFilter::doFilter(HTTPClient &client, HTTPRequest &request, HTTPResponse &response, FilterChain &next)
{
	if (response.status().present())
		return (next());

	try
	{
		HTTPMethodHandler &methodHandler = request.method().get()->handler();

		if (methodHandler.handle(client, request, response))
			next();
	}
	catch (Exception &exception)
	{
		LOG.trace() << "Failed to handle method: " << exception.message() << std::endl;

		response.status(*HTTPStatus::INTERNAL_SERVER_ERROR);
		next();
	}
}
