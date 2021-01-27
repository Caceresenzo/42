/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequestPayloadTooLargeException.hpp            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTPAYLOADTOOLARGEEXCEPTION_HPP_
# define HTTPREQUESTPAYLOADTOOLARGEEXCEPTION_HPP_

#include <http/parser/exception/HTTPRequestException.hpp>
#include <string>

class HTTPRequestPayloadTooLargeException :
		public HTTPRequestException
{
	public:
		HTTPRequestPayloadTooLargeException();
		HTTPRequestPayloadTooLargeException(const std::string &message);
		HTTPRequestPayloadTooLargeException(const HTTPRequestPayloadTooLargeException &other);

		virtual
		~HTTPRequestPayloadTooLargeException() throw ();

		HTTPRequestPayloadTooLargeException&
		operator=(const HTTPRequestPayloadTooLargeException &other);
};

#endif /* HTTPREQUESTPAYLOADTOOLARGEEXCEPTION_HPP_ */
