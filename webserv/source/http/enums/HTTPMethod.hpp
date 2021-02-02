/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPMethod.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:32:53 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/10 16:05:57 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPMETHOD_HPP_
# define HTTPMETHOD_HPP_

#include <util/Convert.hpp>
#include <util/Enum.hpp>
#include <string>

class HTTPMethodHandler;

class HTTPMethod :
		public Enum<HTTPMethod>
{
	private:
		bool m_hasBody;
		HTTPMethodHandler *m_handler;

	public:
		HTTPMethod(void);
		HTTPMethod(bool hasBody, HTTPMethodHandler *handler);
		HTTPMethod(const HTTPMethod &other);

		virtual
		~HTTPMethod(void);

		HTTPMethod&
		operator =(const HTTPMethod &other);

		bool
		hasBody(void) const;

		HTTPMethodHandler&
		handler(void) const;

	public:
		static const HTTPMethod *GET;
		static const HTTPMethod *HEAD;
		static const HTTPMethod *POST;
		static const HTTPMethod *PUT;
		static const HTTPMethod *DELETE;
		static const HTTPMethod *CONNECT;
		static const HTTPMethod *OPTIONS;
		static const HTTPMethod *TRACE;
};

#endif /* HTTPMETHOD_HPP_ */
