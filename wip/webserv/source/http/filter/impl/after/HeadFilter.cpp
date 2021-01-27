/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeadFilter.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 00:35:58 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/10 13:24:07 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/enums/HTTPMethod.hpp>
#include <http/filter/FilterChain.hpp>
#include <http/filter/impl/after/HeadFilter.hpp>
#include <http/request/HTTPRequest.hpp>
#include <http/response/HTTPResponse.hpp>
#include <stddef.h>
#include <util/Macros.hpp>
#include <util/Optional.hpp>

HeadFilter::HeadFilter()
{
}

HeadFilter::HeadFilter(const HeadFilter &other)
{
	(void)other;
}

HeadFilter::~HeadFilter()
{
}

HeadFilter&
HeadFilter::operator=(const HeadFilter &other)
{
	(void)other;

	return (*this);
}

void
HeadFilter::doFilter(UNUSED HTTPClient &client, UNUSED HTTPRequest &request, HTTPResponse &response, FilterChain &next)
{
	if (request.method().equals(HTTPMethod::HEAD))
		response.body(NULL);

	return (next());
}
