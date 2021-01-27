/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FinalFilter.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 01:19:41 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/22 11:36:28 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/filter/FilterChain.hpp>
#include <http/filter/impl/after/FinalFilter.hpp>
#include <http/header/HTTPHeaderFields.hpp>
#include <http/HTTPClient.hpp>
#include <http/request/HTTPRequest.hpp>
#include <http/response/HTTPResponse.hpp>
#include <io/Socket.hpp>
#include <nio/NIOSelector.hpp>
#include <util/Macros.hpp>
#include <util/Optional.hpp>
#include <util/StringUtils.hpp>
#include <string>

FinalFilter::FinalFilter()
{
}

FinalFilter::FinalFilter(const FinalFilter &other)
{
	(void)other;
}

FinalFilter::~FinalFilter()
{
}

FinalFilter&
FinalFilter::operator=(const FinalFilter &other)
{
	(void)other;

	return (*this);
}

void
FinalFilter::doFilter(HTTPClient &client, UNUSED HTTPRequest &request, HTTPResponse &response, FilterChain &next)
{
	if (response.status().get()->isError() || request.headers().get(HTTPHeaderFields::CONNECTION).equals(HTTPHeaderFields::CLOSE))
	{
		if (!(response.status().get() == HTTPStatus::PAYLOAD_TOO_LARGE))
		{
			client.keepAlive(false);
			response.headers().connection(HTTPHeaderFields::CLOSE);
		}
	}

	if (!response.body() && response.headers().get(HTTPHeaderFields::TRANSFER_ENCODING).otherwise(response.headers().get(HTTPHeaderFields::CONTENT_LENGTH)).absent())
	{
		response.headers().contentLength(0);
	}

	response.headers().date();
	response.headers().server();
	response.end();

	NIOSelector::instance().update(client.socket(), NIOSelector::WRITE);

	return (next());
}
