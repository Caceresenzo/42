/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPBodyEncodingException.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPBODYENCODINGEXCEPTION_HPP_
# define HTTPBODYENCODINGEXCEPTION_HPP_

#include <exception/RuntimeException.hpp>
#include <string>

class HTTPBodyEncodingException :
		public RuntimeException
{
	public:
		HTTPBodyEncodingException();
		HTTPBodyEncodingException(const std::string &message);
		HTTPBodyEncodingException(const HTTPBodyEncodingException &other);

		virtual
		~HTTPBodyEncodingException() throw ();

		HTTPBodyEncodingException&
		operator=(const HTTPBodyEncodingException &other);
};

#endif /* HTTPBODYENCODINGEXCEPTION_HPP_ */
