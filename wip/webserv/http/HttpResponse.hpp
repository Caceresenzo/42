/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:38:46 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/27 16:38:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_HTTPRESPONSE_HPP_
# define HTTP_HTTPRESPONSE_HPP_

#include <http/HTTPHeaderFields.hpp>
#include <http/HTTPStatus.hpp>
#include <http/HTTPVersion.hpp>
#include <sys/_types/_ssize_t.h>
#include <util/Byte.hpp>
#include <iostream>
#include <map>

# define AWAITING_BUFFER_SIZE 512

class HttpResponse
{
	public:
		class StatusLine
		{
			private:
				HTTPVersion m_version;
				HTTPStatus m_status;

			public:
				StatusLine(void);
				StatusLine(const HTTPStatus &status);
				StatusLine(const HTTPVersion &version, const HTTPStatus &status);
				StatusLine(const StatusLine &other);

				virtual
				~StatusLine();

				StatusLine&
				operator=(const StatusLine &other);

				std::string
				format(void) const;
		};

		class IBody
		{
			public:
				virtual
				~IBody();

				virtual ssize_t
				write(int fd) = 0;
		};

		class FileBody :
				public IBody
		{
			private:
				int m_fd;
				byte m_buffer[AWAITING_BUFFER_SIZE];

			public:
				FileBody(int fd);

				virtual
				~FileBody();

				virtual ssize_t
				write(int fd);
		};

		enum State
		{
			NONE = 0,
			STATUS_LINE,
			HEADERS,
			EMPTY_LINE,
			BODY,
			FINISHED,
		};

	private:
		StatusLine m_statusLine;
		HTTPHeaderFields m_headers;
		IBody *m_body;
		State m_state;
		ssize_t m_state_index;

	public:
		HttpResponse(const HTTPVersion &version, const HTTPStatus &status, HTTPHeaderFields headers, IBody *body);

		virtual
		~HttpResponse();

		ssize_t
		write(int fd);
};

#endif /* HTTP_HTTPRESPONSE_HPP_ */
