/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPStatus.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:07:46 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/27 15:07:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <http/HTTPStatus.hpp>

#define DEFINE_HTTP_STATUS(name, code, phrase) ENUM_DEFINE(HTTPStatus, name, HTTPStatus(code, phrase));

DEFINE_HTTP_STATUS(CONTINUE/*                           */,100, "Continue");
DEFINE_HTTP_STATUS(SWITCHING_PROTOCOLS/*                */,101, "Switching Protocols");
DEFINE_HTTP_STATUS(PROCESSING/*                         */,102, "Processing");
DEFINE_HTTP_STATUS(CHECKPOINT/*                         */,103, "Checkpoint");
DEFINE_HTTP_STATUS(OK/*                                 */,200, "OK");
DEFINE_HTTP_STATUS(CREATED/*                            */,201, "Created");
DEFINE_HTTP_STATUS(ACCEPTED/*                           */,202, "Accepted");
DEFINE_HTTP_STATUS(NON_AUTHORITATIVE_INFORMATION/*      */,203, "Non-Authoritative Information");
DEFINE_HTTP_STATUS(NO_CONTENT/*                         */,204, "No Content");
DEFINE_HTTP_STATUS(RESET_CONTENT/*                      */,205, "Reset Content");
DEFINE_HTTP_STATUS(PARTIAL_CONTENT/*                    */,206, "Partial Content");
DEFINE_HTTP_STATUS(MULTI_STATUS/*                       */,207, "Multi-Status");
DEFINE_HTTP_STATUS(ALREADY_REPORTED/*                   */,208, "Already Reported");
DEFINE_HTTP_STATUS(IM_USED/*                            */,226, "IM Used");
DEFINE_HTTP_STATUS(MULTIPLE_CHOICES/*                   */,300, "Multiple Choices");
DEFINE_HTTP_STATUS(MOVED_PERMANENTLY/*                  */,301, "Moved Permanently");
DEFINE_HTTP_STATUS(FOUND/*                              */,302, "Found");
DEFINE_HTTP_STATUS(MOVED_TEMPORARILY/*                  */,302, "Moved Temporarily");
DEFINE_HTTP_STATUS(SEE_OTHER/*                          */,303, "See Other");
DEFINE_HTTP_STATUS(NOT_MODIFIED/*                       */,304, "Not Modified");
DEFINE_HTTP_STATUS(USE_PROXY/*                          */,305, "Use Proxy");
DEFINE_HTTP_STATUS(TEMPORARY_REDIRECT/*                 */,307, "Temporary Redirect");
DEFINE_HTTP_STATUS(PERMANENT_REDIRECT/*                 */,308, "Permanent Redirect");
DEFINE_HTTP_STATUS(BAD_REQUEST/*                        */,400, "Bad Request");
DEFINE_HTTP_STATUS(UNAUTHORIZED/*                       */,401, "Unauthorized");
DEFINE_HTTP_STATUS(PAYMENT_REQUIRED/*                   */,402, "Payment Required");
DEFINE_HTTP_STATUS(FORBIDDEN/*                          */,403, "Forbidden");
DEFINE_HTTP_STATUS(NOT_FOUND/*                          */,404, "Not Found");
DEFINE_HTTP_STATUS(METHOD_NOT_ALLOWED/*                 */,405, "Method Not Allowed");
DEFINE_HTTP_STATUS(NOT_ACCEPTABLE/*                     */,406, "Not Acceptable");
DEFINE_HTTP_STATUS(PROXY_AUTHENTICATION_REQUIRED/*      */,407, "Proxy Authentication Required");
DEFINE_HTTP_STATUS(REQUEST_TIMEOUT/*                    */,408, "Request Timeout");
DEFINE_HTTP_STATUS(CONFLICT/*                           */,409, "Conflict");
DEFINE_HTTP_STATUS(GONE/*                               */,410, "Gone");
DEFINE_HTTP_STATUS(LENGTH_REQUIRED/*                    */,411, "Length Required");
DEFINE_HTTP_STATUS(PRECONDITION_FAILED/*                */,412, "Precondition Failed");
DEFINE_HTTP_STATUS(PAYLOAD_TOO_LARGE/*                  */,413, "Payload Too Large");
DEFINE_HTTP_STATUS(REQUEST_ENTITY_TOO_LARGE/*           */,413, "Request Entity Too Large");
DEFINE_HTTP_STATUS(URI_TOO_LONG/*                       */,414, "URI Too Long");
DEFINE_HTTP_STATUS(REQUEST_URI_TOO_LONG/*               */,414, "Request-URI Too Long");
DEFINE_HTTP_STATUS(UNSUPPORTED_MEDIA_TYPE/*             */,415, "Unsupported Media Type");
DEFINE_HTTP_STATUS(REQUESTED_RANGE_NOT_SATISFIABLE/*    */,416, "Requested range not satisfiable");
DEFINE_HTTP_STATUS(EXPECTATION_FAILED/*                 */,417, "Expectation Failed");
DEFINE_HTTP_STATUS(I_AM_A_TEAPOT/*                      */,418, "I'm a teapot");
DEFINE_HTTP_STATUS(INSUFFICIENT_SPACE_ON_RESOURCE/*     */,419, "Insufficient Space On Resource");
DEFINE_HTTP_STATUS(METHOD_FAILURE/*                     */,420, "Method Failure");
DEFINE_HTTP_STATUS(DESTINATION_LOCKED/*                 */,421, "Destination Locked");
DEFINE_HTTP_STATUS(UNPROCESSABLE_ENTITY/*               */,422, "Unprocessable Entity");
DEFINE_HTTP_STATUS(LOCKED/*                             */,423, "Locked");
DEFINE_HTTP_STATUS(FAILED_DEPENDENCY/*                  */,424, "Failed Dependency");
DEFINE_HTTP_STATUS(TOO_EARLY/*                          */,425, "Too Early");
DEFINE_HTTP_STATUS(UPGRADE_REQUIRED/*                   */,426, "Upgrade Required");
DEFINE_HTTP_STATUS(PRECONDITION_REQUIRED/*              */,428, "Precondition Required");
DEFINE_HTTP_STATUS(TOO_MANY_REQUESTS/*                  */,429, "Too Many Requests");
DEFINE_HTTP_STATUS(REQUEST_HEADER_FIELDS_TOO_LARGE/*    */,431, "Request Header Fields Too Large");
DEFINE_HTTP_STATUS(UNAVAILABLE_FOR_LEGAL_REASONS/*      */,451, "Unavailable For Legal Reasons");
DEFINE_HTTP_STATUS(INTERNAL_SERVER_ERROR/*              */,500, "Internal Server Error");
DEFINE_HTTP_STATUS(NOT_IMPLEMENTED/*                    */,501, "Not Implemented");
DEFINE_HTTP_STATUS(BAD_GATEWAY/*                        */,502, "Bad Gateway");
DEFINE_HTTP_STATUS(SERVICE_UNAVAILABLE/*                */,503, "Service Unavailable");
DEFINE_HTTP_STATUS(GATEWAY_TIMEOUT/*                    */,504, "Gateway Timeout");
DEFINE_HTTP_STATUS(HTTP_VERSION_NOT_SUPPORTED/*         */,505, "HTTP Version not supported");
DEFINE_HTTP_STATUS(VARIANT_ALSO_NEGOTIATES/*            */,506, "Variant Also Negotiates");
DEFINE_HTTP_STATUS(INSUFFICIENT_STORAGE/*               */,507, "Insufficient Storage");
DEFINE_HTTP_STATUS(LOOP_DETECTED/*                      */,508, "Loop Detected");
DEFINE_HTTP_STATUS(BANDWIDTH_LIMIT_EXCEEDED/*           */,509, "Bandwidth Limit Exceeded");
DEFINE_HTTP_STATUS(NOT_EXTENDED/*                       */,510, "Not Extended");

#undef DEFINE_HTTP_STATUS

HTTPStatus::HTTPStatus(void) :
		m_code(0),
		m_reasonPhrase()
{
}

HTTPStatus::HTTPStatus(int code, const std::string &phrase) :
		m_code(code),
		m_reasonPhrase(phrase)
{
}

HTTPStatus::HTTPStatus(const HTTPStatus &other) :
		m_code(other.m_code),
		m_reasonPhrase(other.m_reasonPhrase)
{
}

HTTPStatus::~HTTPStatus(void)
{
}

HTTPStatus&
HTTPStatus::operator =(const HTTPStatus &other)
{
	if (this != &other)
	{
		m_code = other.m_code;
		m_reasonPhrase = other.m_reasonPhrase;
	}

	return (*this);
}

int
HTTPStatus::code(void) const
{
	return (m_code);
}

const std::string&
HTTPStatus::reasonPhrase(void) const
{
	return (m_reasonPhrase);
}
