/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IndexFilter.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 23:46:45 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/25 16:49:05 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/LocationBlock.hpp>
#include <http/enums/HTTPMethod.hpp>
#include <http/filter/FilterChain.hpp>
#include <http/filter/impl/before/IndexFilter.hpp>
#include <http/request/HTTPRequest.hpp>
#include <io/File.hpp>
#include <util/Enum.hpp>
#include <util/Macros.hpp>
#include <util/Optional.hpp>
#include <list>
#include <string>

IndexFilter::IndexFilter()
{
}

IndexFilter::IndexFilter(const IndexFilter &other)
{
	(void)other;
}

IndexFilter::~IndexFilter()
{
}

IndexFilter&
IndexFilter::operator =(const IndexFilter &other)
{
	(void)other;

	return (*this);
}

void
IndexFilter::doFilter(UNUSED HTTPClient &client, HTTPRequest &request, UNUSED HTTPResponse &response, FilterChain &next)
{
	Optional<const HTTPMethod*> methodOpt = request.method();
	if (methodOpt.absent())
		return (next());

	const HTTPMethod &method = *methodOpt.get();

	if (!(method == *HTTPMethod::GET || method == *HTTPMethod::HEAD))
		return (next());

	File targetFile(request.targetFile());
	if (!(targetFile.exists() && targetFile.isDirectory()))
		return (next());

	if (request.locationBlock().absent())
		return (next());

	const LocationBlock &locationBlock = *request.locationBlock().get();
	if (locationBlock.index().absent())
		return (next());

	const std::list<std::string> &indexFiles = locationBlock.index().get();
	for (std::list<std::string>::const_iterator it = indexFiles.begin(); it != indexFiles.end(); it++)
	{
		File anIndex(targetFile, *it);

		if (anIndex.exists() && anIndex.isFile())
		{
			request.resource(File(request.resource(), *it).path());
			break;
		}
	}

	return (next());
}
