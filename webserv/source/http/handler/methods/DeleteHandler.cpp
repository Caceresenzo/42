/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:13:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 18:13:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/enums/HTTPStatus.hpp>
#include <http/handler/methods/DeleteHandler.hpp>
#include <http/request/HTTPRequest.hpp>
#include <http/response/HTTPResponse.hpp>
#include <io/File.hpp>
#include <util/Macros.hpp>

DeleteHandler::DeleteHandler()
{
}

DeleteHandler::DeleteHandler(const DeleteHandler &other)
{
	(void)other;
}

DeleteHandler::~DeleteHandler()
{
}

DeleteHandler&
DeleteHandler::operator =(const DeleteHandler &other)
{
	(void)other;

	return (*this);
}

bool
DeleteHandler::handle(UNUSED HTTPClient &client, HTTPRequest &request, HTTPResponse &response)
{
	File targetFile(request.targetFile());

	if (!targetFile.exists())
		response.status(*HTTPStatus::NO_CONTENT);
	else
	{
		if (targetFile.tryRemove())
			response.status(*HTTPStatus::OK);
		else
			response.status(*HTTPStatus::ACCEPTED);
	}

	return (true);
}
