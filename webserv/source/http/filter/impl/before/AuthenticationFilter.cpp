/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AuthenticationFilter.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:49:17 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/06 18:49:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/AuthBlock.hpp>
#include <http/enums/HTTPStatus.hpp>
#include <http/filter/FilterChain.hpp>
#include <http/filter/impl/before/AuthenticationFilter.hpp>
#include <http/header/HTTPHeaderFields.hpp>
#include <http/request/HTTPRequest.hpp>
#include <http/response/HTTPResponse.hpp>
#include <stddef.h>
#include <util/Macros.hpp>
#include <util/Optional.hpp>
#include <util/StringUtils.hpp>
#include <string>

AuthenticationFilter::AuthenticationFilter()
{
}

AuthenticationFilter::AuthenticationFilter(const AuthenticationFilter &other)
{
	(void)other;
}

AuthenticationFilter::~AuthenticationFilter()
{
}

AuthenticationFilter&
AuthenticationFilter::operator=(const AuthenticationFilter &other)
{
	(void)other;

	return (*this);
}

void
AuthenticationFilter::doFilter(UNUSED HTTPClient &client, HTTPRequest &request, HTTPResponse &response, FilterChain &next)
{
	Optional<const AuthBlock*> authBlockOpt = request.authBlock();
	if (authBlockOpt.absent())
		return (next());

	const AuthBlock &authBlock = *authBlockOpt.get();

	Optional<std::string> authorizationOptional = request.headers().get(HTTPHeaderFields::AUTHORIZATION);
	if (authorizationOptional.present())
	{
		const std::string &authorization = authorizationOptional.get();

		size_t pos = authorization.find(' ');
		if (pos != std::string::npos)
		{
			std::string type = authorization.substr(0, pos);
			std::string credentials = authorization.substr(pos + 1);

			if (StringUtils::equalsIgnoreCase(authBlock.type(), type) && authBlock.authorize(credentials))
				return (next());
		}
	}

	response.headers().wwwAuthenticate(authBlock.type(), authBlock.realm());
	response.status(*HTTPStatus::UNAUTHORIZED);
	response.end();
}
