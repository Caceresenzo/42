/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PutHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:43:22 by alicetetu         #+#    #+#             */
/*   Updated: 2020/12/25 10:43:22 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/enums/HTTPStatus.hpp>
#include <http/handler/methods/PutHandler.hpp>
#include <http/handler/methods/task/PutTask.hpp>
#include <http/HTTPClient.hpp>
#include <http/request/HTTPRequest.hpp>
#include <http/response/HTTPResponse.hpp>
#include <sys/fcntl.h>

PutHandler::PutHandler()
{
}

PutHandler::PutHandler(const PutHandler &other)
{
	(void)other;
}

PutHandler::~PutHandler()
{
}

PutHandler&
PutHandler::operator =(const PutHandler &other)
{
	(void)other;

	return (*this);
}

bool
PutHandler::handle(HTTPClient &client, HTTPRequest &request, HTTPResponse &response)
{
	File targetFile(request.targetFile());

	bool justCreated = false;
	
	if (targetFile.exists())
	{
		if (targetFile.isDirectory() || !targetFile.isFile())
		{
			response.status(*HTTPStatus::OK);
			return (true);
		}
	}
	else
	{
		try
		{
			targetFile.createNewFile(0777);
			justCreated = true;
		}
		catch (Exception &exception)
		{
			response.status(*HTTPStatus::INTERNAL_SERVER_ERROR);
			return (true);
		}
	}
	
	FileDescriptor &fd = *targetFile.open(O_WRONLY | O_TRUNC);

	client.task(*(new PutTask(client, fd, justCreated)));

	return (false);
}
