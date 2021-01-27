/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:51:19 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/06 18:51:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE_HPP_
# define HTTPRESPONSE_HPP_

#include <buffer/impl/BaseBuffer.hpp>
#include <http/enums/HTTPStatus.hpp>
#include <http/header/HTTPHeaderFields.hpp>
#include <util/Optional.hpp>

class IResponseBody;

class HTTPStatus;

class HTTPResponse
{
	public:
		class IBody;

		enum State
		{
			S_NONE,
			S_HEADERS,
			S_BODY,
			S_FLUSH
		};

	private:
		Optional<const HTTPStatus*> m_status;
		HTTPHeaderFields m_headers;
		IResponseBody *m_body;
		bool m_ended;

	public:
		State m_state;

	public:
		HTTPResponse();
		HTTPResponse(const HTTPResponse &other);

		virtual
		~HTTPResponse();

		HTTPResponse&
		operator=(const HTTPResponse &other);

		void
		status(const HTTPStatus &status);

		Optional<const HTTPStatus*>&
		status();

		HTTPHeaderFields&
		headers();

		void
		body(IResponseBody *body, bool deletePrevious = true);

		IResponseBody*
		body();

		void
		end();

		bool
		ended();

		void
		string(const std::string &content);

		bool
		store(BaseBuffer &buffer);

};

#endif /* HTTPRESPONSE_HPP_ */
