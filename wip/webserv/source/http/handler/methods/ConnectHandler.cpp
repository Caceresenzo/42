/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:02:05 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 18:02:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/enums/HTTPStatus.hpp>
#include <http/handler/methods/ConnectHandler.hpp>
#include <http/response/HTTPResponse.hpp>
#include <util/Macros.hpp>

ConnectHandler::ConnectHandler()
{
}

ConnectHandler::ConnectHandler(const ConnectHandler &other)
{
	(void)other;
}

ConnectHandler::~ConnectHandler()
{
}

ConnectHandler&
ConnectHandler::operator =(const ConnectHandler &other)
{
	(void)other;

	return (*this);
}

bool
ConnectHandler::handle(UNUSED HTTPClient &client, UNUSED HTTPRequest &request, HTTPResponse &response)
{
	response.status(*HTTPStatus::BAD_REQUEST);

	return (true);
}
