/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequestHeaderTooBigException.hpp               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTHEADERTOOBIGEXCEPTION_HPP_
# define HTTPREQUESTHEADERTOOBIGEXCEPTION_HPP_

#include <http/parser/exception/HTTPRequestException.hpp>
#include <string>

class HTTPRequestHeaderTooBigException :
		public HTTPRequestException
{
	public:
		HTTPRequestHeaderTooBigException();
		HTTPRequestHeaderTooBigException(const std::string &message);
		HTTPRequestHeaderTooBigException(const HTTPRequestHeaderTooBigException &other);

		virtual
		~HTTPRequestHeaderTooBigException() throw ();

		HTTPRequestHeaderTooBigException&
		operator=(const HTTPRequestHeaderTooBigException &other);
};

#endif /* HTTPREQUESTHEADERTOOBIGEXCEPTION_HPP_ */
