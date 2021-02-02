/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PutHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:43:31 by alicetetu         #+#    #+#             */
/*   Updated: 2020/12/25 10:43:31 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUTHANDLER_HPP_
# define PUTHANDLER_HPP_

#include <http/handler/HTTPMethodHandler.hpp>
#include <io/File.hpp>
#include <util/Singleton.hpp>

class PutHandler :
		public HTTPMethodHandler,
		public Singleton<PutHandler>
{
	public:
		PutHandler();
		PutHandler(const PutHandler &other);

		virtual
		~PutHandler();

		PutHandler&
		operator =(const PutHandler &other);

		bool
		handle(HTTPClient &client, HTTPRequest &request, HTTPResponse &response);
};

#endif /* PutHANDLER_HPP_ */
