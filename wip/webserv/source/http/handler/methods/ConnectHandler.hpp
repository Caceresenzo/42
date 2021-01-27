/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:02:05 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 18:02:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTHANDLER_HPP_
# define CONNECTHANDLER_HPP_

#include <http/handler/HTTPMethodHandler.hpp>
#include <util/Singleton.hpp>

class ConnectHandler :
		public HTTPMethodHandler,
		public Singleton<ConnectHandler>
{
	public:
		ConnectHandler();
		ConnectHandler(const ConnectHandler &other);

		virtual
		~ConnectHandler();

		ConnectHandler&
		operator =(const ConnectHandler &other);

		bool
		handle(HTTPClient &client, HTTPRequest &request, HTTPResponse &response);
};

#endif /* CONNECTHANDLER_HPP_ */
