/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequestURLTooLongException.hpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTURLTOOLONGEXCEPTION_HPP_
# define HTTPREQUESTURLTOOLONGEXCEPTION_HPP_

#include <http/parser/exception/HTTPRequestException.hpp>
#include <string>

class HTTPRequestURLTooLongException :
		public HTTPRequestException
{
	public:
		HTTPRequestURLTooLongException();
		HTTPRequestURLTooLongException(const std::string &message);
		HTTPRequestURLTooLongException(const HTTPRequestURLTooLongException &other);

		virtual
		~HTTPRequestURLTooLongException() throw ();

		HTTPRequestURLTooLongException&
		operator=(const HTTPRequestURLTooLongException &other);
};

#endif /* HTTPREQUESTURLTOOLONGEXCEPTION_HPP_ */
