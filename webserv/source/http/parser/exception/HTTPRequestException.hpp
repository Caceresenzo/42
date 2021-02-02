/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequestException.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTEXCEPTION_HPP_
# define HTTPREQUESTEXCEPTION_HPP_

#include <exception/RuntimeException.hpp>
#include <string>

class HTTPRequestException :
		public RuntimeException
{
	public:
		HTTPRequestException();
		HTTPRequestException(const std::string &message);
		HTTPRequestException(const HTTPRequestException &other);

		virtual
		~HTTPRequestException() throw ();

		HTTPRequestException&
		operator=(const HTTPRequestException &other);
};

#endif /* HTTPREQUESTEXCEPTION_HPP_ */
