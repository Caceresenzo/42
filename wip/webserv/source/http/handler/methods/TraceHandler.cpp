/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TraceHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:42:58 by alicetetu         #+#    #+#             */
/*   Updated: 2020/12/25 10:42:58 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/enums/HTTPMethod.hpp>
#include <http/handler/methods/TraceHandler.hpp>
#include <http/header/HTTPHeaderFields.hpp>
#include <http/request/HTTPRequest.hpp>
#include <http/response/HTTPResponse.hpp>
#include <util/Enum.hpp>
#include <util/Macros.hpp>
#include <util/Optional.hpp>
#include <util/URL.hpp>
#include <string>

TraceHandler::TraceHandler()
{
}

TraceHandler::TraceHandler(const TraceHandler &other)
{
	(void)other;
}

TraceHandler::~TraceHandler()
{
}

TraceHandler&
TraceHandler::operator =(const TraceHandler &other)
{
	(void)other;

	return (*this);
}

bool
TraceHandler::handle(UNUSED HTTPClient &client,  HTTPRequest &request, HTTPResponse &response)
{
	std::string method = request.method().get()->name();
	std::string path = request.url().format();
	std::string version = "HTTP/1.1";
	std::string statusLine = method + ' ' + path + ' ' + version + '\n';
	std::string head = statusLine + request.headers().format("\n");

	response.string(head);
	response.status(*HTTPStatus::OK);
	response.headers().httpMessage();

	return (true);
}
