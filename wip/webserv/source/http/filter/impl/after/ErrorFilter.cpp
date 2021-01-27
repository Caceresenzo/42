/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorFilter.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 00:30:02 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/19 12:27:18 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <buffer/impl/FileDescriptorBuffer.hpp>
#include <config/block/container/CustomErrorMap.hpp>
#include <config/block/ServerBlock.hpp>
#include <exception/Exception.hpp>
#include <http/enums/HTTPStatus.hpp>
#include <http/filter/FilterChain.hpp>
#include <http/filter/impl/after/ErrorFilter.hpp>
#include <http/page/DefaultPages.hpp>
#include <http/request/HTTPRequest.hpp>
#include <http/response/body/impl/FileResponseBody.hpp>
#include <http/response/HTTPResponse.hpp>
#include <io/File.hpp>
#include <io/FileDescriptor.hpp>
#include <log/Logger.hpp>
#include <log/LoggerFactory.hpp>
#include <sys/fcntl.h>
#include <util/helper/DeleteHelper.hpp>
#include <util/Macros.hpp>
#include <util/Optional.hpp>
#include <iostream>
#include <string>

Logger &ErrorFilter::LOG = LoggerFactory::get("Error Filter");

ErrorFilter::ErrorFilter()
{
}

ErrorFilter::ErrorFilter(const ErrorFilter &other)
{
	(void)other;
}

ErrorFilter::~ErrorFilter()
{
}

ErrorFilter&
ErrorFilter::operator=(const ErrorFilter &other)
{
	(void)other;

	return (*this);
}

void
ErrorFilter::doFilter(UNUSED HTTPClient &client, UNUSED HTTPRequest &request, HTTPResponse &response, FilterChain &next)
{
	if (!response.status().present())
		return (next());

	const HTTPStatus &status = *response.status().get();
	if (!status.isError())
		return (next());

	if (response.body() && response.body()->isSelfManaged())
		return (next());

	bool success = false;
	if (request.serverBlock().present())
	{
		const ServerBlock &serverBlock = *request.serverBlock().get();

		if (serverBlock.errors().present())
		{
			const CustomErrorMap &errorMap = serverBlock.errors().get();
			if (errorMap.has(status))
			{
				File errorFile(request.root(), errorMap.get(status));

				FileDescriptor *fd = NULL;
				FileDescriptorBuffer *fdBuffer = NULL;
				try
				{
					fd = errorFile.open(O_RDONLY);
					fdBuffer = FileDescriptorBuffer::from(*fd, FileDescriptorBuffer::CLOSE | FileDescriptorBuffer::DELETE);

					response.body(new FileResponseBody(*fdBuffer));

					success = true;
				}
				catch (Exception &exception)
				{
					if (fdBuffer)
						DeleteHelper::pointer<FileDescriptorBuffer>(fdBuffer);
					else
						DeleteHelper::pointer<FileDescriptor>(fd); /* In case of memory allocation failing for the body. */

					if (LOG.isDebugEnabled())
						LOG.debug() << "Failed to open custom error file: " << exception.message() << std::endl;
				}
			}
		}
	}

	if (!success)
		response.string(DefaultPages::instance().resolve(status));

	return (next());
}
