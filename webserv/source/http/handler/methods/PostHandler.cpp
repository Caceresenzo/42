/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:43:22 by alicetetu         #+#    #+#             */
/*   Updated: 2020/12/25 10:43:22 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/enums/HTTPStatus.hpp>
#include <http/handler/methods/PostHandler.hpp>
#include <http/handler/methods/task/PutTask.hpp>
#include <http/HTTPClient.hpp>
#include <http/request/HTTPRequest.hpp>
#include <http/response/HTTPResponse.hpp>
#include <sys/fcntl.h>

PostHandler::PostHandler()
{
}

PostHandler::PostHandler(const PostHandler &other)
{
	(void)other;
}

PostHandler::~PostHandler()
{
}

PostHandler&
PostHandler::operator =(const PostHandler &other)
{
	(void)other;

	return (*this);
}

bool
PostHandler::handle(HTTPClient &client, HTTPRequest &request, HTTPResponse &response)
{
	File targetFile(request.targetFile());

	bool justCreated = false;

	std::string out;
	
	if (targetFile.exists())
	{
		if (targetFile.isDirectory() || !targetFile.isFile()) // TODO This is not supposed to work like that, but 42 tester....
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
			response.headers().contentLocation(targetFile.path()); // TODO Wrong value returned
			justCreated = true;
		}
		catch (Exception &exception)
		{
			response.status(*HTTPStatus::INTERNAL_SERVER_ERROR);
			return (true);
		}
	}

	FileDescriptor &fd = *targetFile.open(O_WRONLY | O_APPEND);

	if (!justCreated)
		fd.seekToEnd();

	client.task(*(new PutTask(client, fd, justCreated)));

	return (false);
}
