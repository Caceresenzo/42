/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPStatus.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:07:46 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/27 15:07:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSTATUS_HPP_
# define HTTPSTATUS_HPP_

#include <util/Enum.hpp>
#include <string>

class HTTPStatus :
		public Enum<HTTPStatus>
{
	public:
		typedef Enum<HTTPStatus>::iterator iterator;

	private:
		int m_code;
		std::string m_reasonPhrase;

	public:
		HTTPStatus(void);
		HTTPStatus(int code, const std::string &phrase);
		HTTPStatus(const HTTPStatus &other);

		virtual
		~HTTPStatus(void);

		HTTPStatus&
		operator =(const HTTPStatus &other);

		int
		code(void) const;

		const std::string&
		reasonPhrase(void) const;

		inline bool
		isError() const
		{
			return (HTTPStatus::isError(m_code));
		}

	public:
		inline static bool
		isError(int code)
		{
			int d = code / 100;

			return (d == 4 || d == 5);
		}

		inline static const HTTPStatus*
		find(int code)
		{
			const Container &storage = values();

			for (const_iterator it = storage.begin(); it != storage.end(); it++)
				if ((*it)->m_code == code)
					return (*it);

			return (NULL);
		}

	public:
		static const HTTPStatus *CONTINUE;
		static const HTTPStatus *SWITCHING_PROTOCOLS;
		static const HTTPStatus *PROCESSING;
		static const HTTPStatus *CHECKPOINT;
		static const HTTPStatus *OK;
		static const HTTPStatus *CREATED;
		static const HTTPStatus *ACCEPTED;
		static const HTTPStatus *NON_AUTHORITATIVE_INFORMATION;
		static const HTTPStatus *NO_CONTENT;
		static const HTTPStatus *RESET_CONTENT;
		static const HTTPStatus *PARTIAL_CONTENT;
		static const HTTPStatus *MULTI_STATUS;
		static const HTTPStatus *ALREADY_REPORTED;
		static const HTTPStatus *IM_USED;
		static const HTTPStatus *MULTIPLE_CHOICES;
		static const HTTPStatus *MOVED_PERMANENTLY;
		static const HTTPStatus *FOUND;
		static const HTTPStatus *MOVED_TEMPORARILY;
		static const HTTPStatus *SEE_OTHER;
		static const HTTPStatus *NOT_MODIFIED;
		static const HTTPStatus *USE_PROXY;
		static const HTTPStatus *TEMPORARY_REDIRECT;
		static const HTTPStatus *PERMANENT_REDIRECT;
		static const HTTPStatus *BAD_REQUEST;
		static const HTTPStatus *UNAUTHORIZED;
		static const HTTPStatus *PAYMENT_REQUIRED;
		static const HTTPStatus *FORBIDDEN;
		static const HTTPStatus *NOT_FOUND;
		static const HTTPStatus *METHOD_NOT_ALLOWED;
		static const HTTPStatus *NOT_ACCEPTABLE;
		static const HTTPStatus *PROXY_AUTHENTICATION_REQUIRED;
		static const HTTPStatus *REQUEST_TIMEOUT;
		static const HTTPStatus *CONFLICT;
		static const HTTPStatus *GONE;
		static const HTTPStatus *LENGTH_REQUIRED;
		static const HTTPStatus *PRECONDITION_FAILED;
		static const HTTPStatus *PAYLOAD_TOO_LARGE;
		static const HTTPStatus *REQUEST_ENTITY_TOO_LARGE;
		static const HTTPStatus *URI_TOO_LONG;
		static const HTTPStatus *REQUEST_URI_TOO_LONG;
		static const HTTPStatus *UNSUPPORTED_MEDIA_TYPE;
		static const HTTPStatus *REQUESTED_RANGE_NOT_SATISFIABLE;
		static const HTTPStatus *EXPECTATION_FAILED;
		static const HTTPStatus *I_AM_A_TEAPOT;
		static const HTTPStatus *INSUFFICIENT_SPACE_ON_RESOURCE;
		static const HTTPStatus *METHOD_FAILURE;
		static const HTTPStatus *DESTINATION_LOCKED;
		static const HTTPStatus *UNPROCESSABLE_ENTITY;
		static const HTTPStatus *LOCKED;
		static const HTTPStatus *FAILED_DEPENDENCY;
		static const HTTPStatus *TOO_EARLY;
		static const HTTPStatus *UPGRADE_REQUIRED;
		static const HTTPStatus *PRECONDITION_REQUIRED;
		static const HTTPStatus *TOO_MANY_REQUESTS;
		static const HTTPStatus *REQUEST_HEADER_FIELDS_TOO_LARGE;
		static const HTTPStatus *UNAVAILABLE_FOR_LEGAL_REASONS;
		static const HTTPStatus *INTERNAL_SERVER_ERROR;
		static const HTTPStatus *NOT_IMPLEMENTED;
		static const HTTPStatus *BAD_GATEWAY;
		static const HTTPStatus *SERVICE_UNAVAILABLE;
		static const HTTPStatus *GATEWAY_TIMEOUT;
		static const HTTPStatus *HTTP_VERSION_NOT_SUPPORTED;
		static const HTTPStatus *VARIANT_ALSO_NEGOTIATES;
		static const HTTPStatus *INSUFFICIENT_STORAGE;
		static const HTTPStatus *LOOP_DETECTED;
		static const HTTPStatus *BANDWIDTH_LIMIT_EXCEEDED;
		static const HTTPStatus *NOT_EXTENDED;
};

#endif /* HTTP_HTTPSTATUS_HPP_ */
