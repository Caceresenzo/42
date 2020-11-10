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
# include <string>

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

	public:
		static HTTPStatus *CONTINUE;
		static HTTPStatus *SWITCHING_PROTOCOLS;
		static HTTPStatus *PROCESSING;
		static HTTPStatus *CHECKPOINT;
		static HTTPStatus *OK;
		static HTTPStatus *CREATED;
		static HTTPStatus *ACCEPTED;
		static HTTPStatus *NON_AUTHORITATIVE_INFORMATION;
		static HTTPStatus *NO_CONTENT;
		static HTTPStatus *RESET_CONTENT;
		static HTTPStatus *PARTIAL_CONTENT;
		static HTTPStatus *MULTI_STATUS;
		static HTTPStatus *ALREADY_REPORTED;
		static HTTPStatus *IM_USED;
		static HTTPStatus *MULTIPLE_CHOICES;
		static HTTPStatus *MOVED_PERMANENTLY;
		static HTTPStatus *FOUND;
		static HTTPStatus *MOVED_TEMPORARILY;
		static HTTPStatus *SEE_OTHER;
		static HTTPStatus *NOT_MODIFIED;
		static HTTPStatus *USE_PROXY;
		static HTTPStatus *TEMPORARY_REDIRECT;
		static HTTPStatus *PERMANENT_REDIRECT;
		static HTTPStatus *BAD_REQUEST;
		static HTTPStatus *UNAUTHORIZED;
		static HTTPStatus *PAYMENT_REQUIRED;
		static HTTPStatus *FORBIDDEN;
		static HTTPStatus *NOT_FOUND;
		static HTTPStatus *METHOD_NOT_ALLOWED;
		static HTTPStatus *NOT_ACCEPTABLE;
		static HTTPStatus *PROXY_AUTHENTICATION_REQUIRED;
		static HTTPStatus *REQUEST_TIMEOUT;
		static HTTPStatus *CONFLICT;
		static HTTPStatus *GONE;
		static HTTPStatus *LENGTH_REQUIRED;
		static HTTPStatus *PRECONDITION_FAILED;
		static HTTPStatus *PAYLOAD_TOO_LARGE;
		static HTTPStatus *REQUEST_ENTITY_TOO_LARGE;
		static HTTPStatus *URI_TOO_LONG;
		static HTTPStatus *REQUEST_URI_TOO_LONG;
		static HTTPStatus *UNSUPPORTED_MEDIA_TYPE;
		static HTTPStatus *REQUESTED_RANGE_NOT_SATISFIABLE;
		static HTTPStatus *EXPECTATION_FAILED;
		static HTTPStatus *I_AM_A_TEAPOT;
		static HTTPStatus *INSUFFICIENT_SPACE_ON_RESOURCE;
		static HTTPStatus *METHOD_FAILURE;
		static HTTPStatus *DESTINATION_LOCKED;
		static HTTPStatus *UNPROCESSABLE_ENTITY;
		static HTTPStatus *LOCKED;
		static HTTPStatus *FAILED_DEPENDENCY;
		static HTTPStatus *TOO_EARLY;
		static HTTPStatus *UPGRADE_REQUIRED;
		static HTTPStatus *PRECONDITION_REQUIRED;
		static HTTPStatus *TOO_MANY_REQUESTS;
		static HTTPStatus *REQUEST_HEADER_FIELDS_TOO_LARGE;
		static HTTPStatus *UNAVAILABLE_FOR_LEGAL_REASONS;
		static HTTPStatus *INTERNAL_SERVER_ERROR;
		static HTTPStatus *NOT_IMPLEMENTED;
		static HTTPStatus *BAD_GATEWAY;
		static HTTPStatus *SERVICE_UNAVAILABLE;
		static HTTPStatus *GATEWAY_TIMEOUT;
		static HTTPStatus *HTTP_VERSION_NOT_SUPPORTED;
		static HTTPStatus *VARIANT_ALSO_NEGOTIATES;
		static HTTPStatus *INSUFFICIENT_STORAGE;
		static HTTPStatus *LOOP_DETECTED;
		static HTTPStatus *BANDWIDTH_LIMIT_EXCEEDED;
		static HTTPStatus *NOT_EXTENDED;
};

#endif /* HTTP_HTTPSTATUS_HPP_ */
